#include "head.h"

int tcpInit(int *sFd,char* ip,char* port)
{
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    if(socketFd==-1) {
        printf("errno=%d,\n",errno);perror("socket");
        return -1;
    }
    int ret;
    int reuse=1;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    if(ret==-1) {
        printf("errno=%d,\n",errno);perror("setsockopt");
        return -1;
    }
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(port));
    serAddr.sin_addr.s_addr=inet_addr(ip);
    ret=bind(socketFd,(struct sockaddr*)&serAddr,sizeof(struct sockaddr));
    if(ret==-1) {
        printf("errno=%d,\n",errno);perror("bind");
        return -1;
    }
    listen(socketFd,10);
    *sFd=socketFd;
    return 0;

}

