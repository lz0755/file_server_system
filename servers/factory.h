#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"
#include "common.h"
#include "command.h"
#include "mysql_cmd.h"
#define MAX_THREAD 10
#define INIT_CAPACITY 10
typedef struct{
    Que_t que;
    pthread_cond_t cond;
    pthread_t *ppthids;
    int pthNum;
    int isStartFlag;
}Factory_t,*pFactory_t;
int factoryInit(Factory_t *pf,int threadNum,int capacity);
int factoryStart(Factory_t *pf);
void destroyFactory(Factory_t *pf);
void *threadNormalCmd(void *pArg);
int tcpInit(int *sFd,char* ip,char* port);
int transFile(int newFd,char *filename);
#endif
