#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"
#include "common.h"
#include "command.h"
#define MAX_THREAD 10
#define INIT_CAPACITY 10

#define MAX_CILENT 10000
typedef struct{
    Que_t que;
    pthread_cond_t cond;
    pthread_t *ppthids;
    userinfo_t *userInfo_g;
    int pthNum;
    int epfd;
    int isStartFlag;
}Factory_t,*pFactory_t;
int factoryInit(Factory_t *pf,int threadNum,int capacity);
int factoryStart(Factory_t *pf);
void destroyFactory(Factory_t *pf);
void *threadNormalCmd(void *pArg);
int tcpInit(int *sFd,char* ip,char* port);
int epollAdd(int epfd,int fd);
void writeLog(const char *username,const char *info);
void writeCmdLog(const char *username,const cmd_t *pcmd);
#endif
