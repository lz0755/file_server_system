#include "factory.h"
#include "mysql_cmd.h"


int factoryInit(Factory_t *pf,int threadNum,int capacity)
{
    queInit(&pf->que,capacity);
    pthread_cond_init(&pf->cond,NULL);
    pf->ppthids = (pthread_t *)calloc(threadNum,sizeof(pthread_t));
    pf->pthNum = threadNum;
    pf->isStartFlag = 0;
    mysqlInit();
    return 0;
}
void destroyFactory(Factory_t *pf)
{
    queClear(&pf->que);
    pthread_cond_destroy(&pf->cond);
    free(pf->ppthids);
    //printf("destroyFactory call\n");
}
void cleanUpFunc(void *pArg)
{
    Que_t *pq=(Que_t *)pArg;
    pthread_mutex_unlock(&pq->mutex);
}/* 
void *threadTransFile(void *pArg)
{
    Factory_t *pf=(Factory_t *)pArg;
    Que_t *pq = &pf->que;

    while(1){
        pthread_mutex_lock(&pq->mutex);
        Node_t *node;
        pthread_cleanup_push(cleanUpFunc,pq);
        if(isQueEmpty(pq))
            pthread_cond_wait(&pf->cond,&pq->mutex);

        node = quePop(pq);
        pthread_cleanup_pop(1);
        if(node != NULL){
            int newFd=node->socketFd;
            free(node);
            char filename[] = "file";
            transFile(newFd,filename);
            //close(newFd);
        }
    }
}*/

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

void *threadNormalCmd(void *pArg)
{
    Factory_t *pf=(Factory_t *)pArg;
    Que_t *pq = &pf->que;

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
        user_token_t userToken;
        ret = recvCmd(newFd,&cmd);//1接收token认证信息
        if(ret != 0){
            printf("client %d disconnect\n",newFd);
            close(newFd);
            continue;
        }
        //1token认证
        if(cmd.type == TOKEN){
            memcpy(&userToken,cmd.buf,sizeof(user_token_t));
            printf("uid=%d,token=%s\n",userToken.uid,userToken.token);
            ret = tokenCmd(newFd,&userToken,&cmd);//2token认证后发送确认
            if(ret !=0){
                close(newFd);
                continue;
            }
        }
        else
        {
            close(newFd);
            continue;
        }
        
        ret = recvCmd(newFd,&cmd);//3接收上传下载信号

        //printf("cmd:%d\n",cmd.type);
        //writeCmdLog(username,&cmd);
        switch(cmd.type)
        {                                                                                                           
            case PUTS:
            {
                ret = putsCmd(newFd,userToken.uid,&cmd);
                if(ret == -1){
                    close(newFd);
                    goto reStart;
                }
                break;
            }
            case GETS:
            case GETS2:
            {
                if(cmd.buf[0] == '0' || getsCmd(newFd,userToken.uid) == -1)
                {
                    close(newFd);
                    goto reStart;
                }
                break;
            }
            default:
            {
                #ifdef DEBUG_SERVER
                printf("command error\n");
                #endif
                break;
            }
        }
        close(newFd);
    }
}
