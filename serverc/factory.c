#include "factory.h"
#include "mysql_cmd.h"


int factoryInit(Factory_t *pf,int threadNum,int capacity)
{
    queInit(&pf->que,capacity);
    pthread_cond_init(&pf->cond,NULL);
    pf->ppthids = (pthread_t *)calloc(threadNum,sizeof(pthread_t));
    pf->userInfo_g = (userinfo_t*)calloc(10000,sizeof(userinfo_t));
    pf->pthNum = threadNum;
    pf->isStartFlag = 0;
    mysqlConnectionPoolInit();
    return 0;
}
void destroyFactory(Factory_t *pf)
{
    connPoolClear();
    queClear(&pf->que);
    pthread_cond_destroy(&pf->cond);
    free(pf->ppthids);
    printf("destroyFactory call\n");
}
void cleanUpFunc(void *pArg)
{
    Que_t *pq=(Que_t *)pArg;
    pthread_mutex_unlock(&pq->mutex);
}

int factoryStart(Factory_t *pf)
{
    if(!pf->isStartFlag){
        int i;
        for(i=0;i<pf->pthNum;i++)
            pthread_create(pf->ppthids+i,NULL,threadNormalCmd,pf);
        pf->isStartFlag = 1;
    }
    return 0;
}
int epollAdd(int epfd,int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN|EPOLLET;
    evt.data.fd = fd;
    int ret;
    ret = epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&evt);
    if(ret==-1) {
        printf("errno=%d,\n",errno);perror("epoll_ctl");
        return -1;
    }
    return 0;
}
void *threadNormalCmd(void *pArg)
{
    Factory_t *pf=(Factory_t *)pArg;
    Que_t *pq = &pf->que;
    userinfo_t *userInfo_g = pf->userInfo_g;

    while(1){
reStart:
        pthread_mutex_lock(&pq->mutex);
        Node_t *node;
        pthread_cleanup_push(cleanUpFunc,pq);
        //线程等待通知，若此时有通知，准备加锁时，另一个线程刚刚完成任务准备加锁并且在
        //这个线程之前加锁成功此时另一个线程将队列中的任务取走，
        //而该线程等待加锁成功后发现队列中无任务了，所以要判断在队列中取到的值是否为空
        if(isQueEmpty(pq))
            pthread_cond_wait(&pf->cond,&pq->mutex);

        node = quePop(pq);
        pthread_cleanup_pop(1);
        if(node == NULL){
            continue;
        }
        int newFd=node->socketFd;
        free(node);
        int ret;
        cmd_t cmd;
        if(userInfo_g[newFd].sfd != newFd){
            while(1){
                ret = recvCmd(newFd,&cmd);
                //printf("start sign\n");
                if(ret != 0){
                    goto closesfd;
                }
                userinfo_t *userInfo =&userInfo_g[newFd];
                ret = SignCmd(newFd,userInfo->username,&userInfo->userToken,&cmd);
                if(ret == 0){
                    lsCmd(newFd,userInfo->userToken.uid,userInfo->dirid,&cmd);
                    userInfo_g[newFd].sfd=newFd;
                    epollAdd(pf->epfd,newFd);
                    goto reStart;
                }
                else if(ret == -1){
                    continue;
                }
                else{
                    goto closesfd;
                }
            }
            goto reStart;
        }
        
        userinfo_t *userInfo=userInfo_g+newFd;
        unsigned int uid=userInfo->userToken.uid;
        unsigned int *dirid=&userInfo->dirid;
        //writeLog(username,"login success");
        //printf("client %s connect\n",userInfo->username);
        //while(1){
            ret = recvCmd(newFd,&cmd);
            if(ret != 0){
                goto closesfd;
            }
            //printf("cmd:%d %s\n",cmd.type, cmdtext[cmd.type]);
            //writeCmdLog(username,&cmd);
            switch(cmd.type)
            {
                case CD:ret = cdCmd(newFd,uid,dirid,&cmd);break;
                case MKDIR: ret = mkdirCmd(newFd,uid,*dirid,&cmd);break;                                                                                                             
                case RMDIR: ret = rmdirCmd(newFd,uid,*dirid,&cmd);break; 
                case REMOVE:ret = removeCmd(newFd,uid,*dirid,&cmd); break;
                case LS:lsCmd(newFd,uid,*dirid,&cmd);break;                                                                                                          
                case PUTS:
                {
                    ret = putsCmd(newFd,uid,*dirid,&cmd);
                    if(ret == -1){
                        goto reStart;
                    }break;
                }
                case GETS:
                case GETS2:
                {
                    ret = getsCmd(newFd,uid,*dirid,&cmd);
                    if(ret == -1){
                        goto reStart;
                    }
                    break;
                }
                case EXIT:goto closesfd;
                case OTHER:
                #ifdef DEBUG_SERVER
                printf("command error\n");
                #endif
                break;
                default:break;
            }
            autoUpdateToken(&userInfo->userToken);
            if((cmd.type == CD || cmd.type == MKDIR || cmd.type == RMDIR || cmd.type == REMOVE))
            {
                if(ret == 0){
                    cmd.buf[0]='1';
                    if(cmd.type==CD){
                        struct uint_t id;
                        id.uint32=*dirid;
                        memcpy(cmd.buf+1,&id,sizeof(id));
                        sendCmd(newFd,&cmd,CD,sizeof(id)+1);//send dirid
                    }
                    else
                        sendCmd(newFd,&cmd,cmd.type,1);//成功
                }
                else{
                    cmd.buf[0]='0';//失败
                    sendCmd(newFd,&cmd,cmd.type,1);
                }
            }
        //}
        goto reStart;
closesfd:
        printf("client %d disconnect\n",newFd);
        epoll_ctl(pf->epfd,EPOLL_CTL_DEL,newFd,NULL);
        close(newFd);
        memset(userInfo_g+newFd,0,sizeof(userinfo_t));
    }
}
