#include "factory.h"


const char cmdtext[][20]={
    "","cd","ls","mkdir","rmdir","puts","gets","gets again","remove","pwd","exit",
    "login","login success","login failed","other"
};

int factoryInit(Factory_t *pf,int threadNum,int capacity)
{
    queInit(&pf->que,capacity);
    pthread_cond_init(&pf->cond,NULL);
    pf->ppthids = (pthread_t *)calloc(threadNum,sizeof(pthread_t));
    pf->pthNum = threadNum;
    pf->isStartFlag = 0;
    return 0;
}
void destroyFactory(Factory_t *pf)
{
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
            pthread_create(pf->ppthids+i,NULL,threadUpDown,pf);
        pf->isStartFlag = 1;
    }
    return 0;
}
int tcp_connect(const char* ip, int port) //用于客户端的连接
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);//向系统注册申请新的socket
    if (sfd == -1)
    {
        perror("socket");
        exit(-1);

    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(struct sockaddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(ip);
    if (connect(sfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr)) == -1)
    {//将sfd连接至制定的服务器网络地址serveraddr
        perror("connect");
        close(sfd);
        return -1;//exit(-1);
    }
    return sfd;
}

void *threadUpDown(void *pArg)
{
    Factory_t *pf=(Factory_t *)pArg;
    Que_t *pq = &pf->que;

    while(1){
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
        int newFd = tcp_connect(node->ip,node->port);
        if(newFd == -1){
            printf("can't connect server %s:%d\n",node->ip,node->port);
            free(node);
            continue;
        }
        //printf("client newFd=%d\n",newFd);
        msg_fileinfo_t *pfileInfo=&node->fileinfo;
        cmd_t cmd;
        int ret;
        //user_token_t *userToken=&pf->userToken;
        //printf("uid=%d,token=%s\n",pf->userToken.uid,pf->userToken.token);
        memcpy(cmd.buf,&pf->userToken,sizeof(pf->userToken));
        sendCmd(newFd,&cmd,TOKEN,sizeof(pf->userToken));//1发送token认证
        ret = recvCmd(newFd,&cmd);//2接收确认
        if(cmd.type!=TOKEN || cmd.buf[0] != '1'){
            printf("%d token identification failed\n",pf->userToken.uid);
            goto reStart;
        }
        cmd.type=pf->cmdType;
        if(GETS==cmd.type || GETS2==cmd.type)
        {
            recvFile(newFd,'0',pfileInfo,cmd.type);//3接收文件
        }
        else if(PUTS==cmd.type){
            ret = sendFile(newFd,'0',pfileInfo,0,PUTS);//3发送文件
            if(ret == -1)
                goto reStart;
            //发送当前目录
            struct uint_t id;
            id.uint32=pf->curDirId;
            memcpy(cmd.buf,&id,sizeof(id));
            sendCmd(newFd,&cmd,PUTS,sizeof(id));//6发送当前目录id
        }
reStart:
        free(node);
        close(newFd);
    }
}
