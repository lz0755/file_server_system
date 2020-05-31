#include "factory.h"
#include "config.h"
#define SERVER_FILEPATH "/home/laiyufeng/baidudir"
int exitFds[2];
void sigExitFunc(int signum)
{
    write(exitFds[1],&signum,1);
}
int epollAdd(int epfd,int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;
    int ret;
    ret = epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&evt);
    if(ret==-1) {
        printf("errno=%d,\n",errno);perror("epoll_ctl");
        return -1;
    }
    return 0;
}
int main(int argc,char* argv[])
{
    //ARGS_CHECK(argc,5);
    //watch maybe crash,fix it
    pipe(exitFds);
    unsigned char flag = 2;
    while(fork()){
        if(flag>0){
            flag--;
            close(exitFds[0]);
        }
        signal(SIGUSR1,sigExitFunc);
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            printf("exit success\n");
            exit(0);
        }
    }
    if(flag>0){
        flag--;
        close(exitFds[1]);
    }
    int socketFd, newFd;
    int ret;
    int threadNum=MAX_THREAD;
    int capacity = INIT_CAPACITY;
    ret = initConfig();
    if(ret ==-1){
        printf("config file error\n");
        return -1;
    }
    
    char *ip,*port,*serverpath;
    ip=getConfig("server_ip");
    port=getConfig("server_port");
    serverpath=getConfig("server_path");
    if(ip==NULL || port==NULL || serverpath==NULL){
        printf("config doesnot exist\n");
        return -1;
    }

    //printf("ip=%s,port=%s\n",ip,port);
    ret = tcpInit(&socketFd,ip,port);
    if(ret==-1) {
        return -1;
    }
    Factory_t mainFactory;
    factoryInit(&mainFactory,threadNum,capacity);
    factoryStart(&mainFactory);
    int epfd = epoll_create(1);
    struct epoll_event evts[2];
    //evts = (struct epoll_event*)calloc(processNum+1,sizeof(struct epoll_event));
    
    epollAdd(epfd,socketFd);
    epollAdd(epfd,exitFds[0]);
    //accept接收任务，循环遍历，找到非忙碌子进程，将任务发送给它
    //如果发现子进程的管道对端可读，找到对应子进程，将其标识为非忙碌
    int readFdCount;
    Que_t *pMainQue = &mainFactory.que;
    chdir(SERVER_FILEPATH);
    int i=0,j=0;
    printf("Welcome come!\n");
    while(1)
    {
        readFdCount = epoll_wait(epfd,evts,2,-1);//-1表示永久阻塞
        for(i = 0; i< readFdCount;i++)
        {
            if(evts[i].data.fd == socketFd){
                newFd = accept(socketFd,NULL,NULL);
                //printf("client socketfd %d\n",pNode->socketFd);
                Node_t *pNode=(Node_t *)malloc(sizeof(Node_t));
                pNode->socketFd = newFd;
                pNode->next = NULL;
                quePush(pMainQue,pNode);
                pthread_cond_signal(&mainFactory.cond);
            }
            if(evts[i].data.fd == exitFds[0]){
                char t;
                read(exitFds[0],&t,1);

                for(j = 0;j<threadNum;j++){
                    pthread_cancel(mainFactory.ppthids[j]);    
                }
                for(j = 0;j<threadNum;j++){
                    pthread_join(mainFactory.ppthids[j],NULL);
                }
                close(socketFd);
                destroyFactory(&mainFactory);
                exit(0);
            }
        }
    }
    return 0;
}

