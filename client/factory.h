#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"
#include "common.h"

#define SERVER_IP   "192.168.5.199"
#define SERVER_PORT "6666"
#define MAX_THREAD 10
#define INIT_CAPACITY 10

typedef struct{
    // Que_t queDw;
    // Que_t queUp;
    // pthread_cond_t condDw;
    // pthread_cond_t condUp;
    Que_t que;
    pthread_cond_t cond;
    pthread_t *ppthids;
    user_token_t userToken;
    unsigned int curDirId;
    int cmdType;
    int pthNum;
    int isStartFlag;
}Factory_t,*pFactory_t;
int factoryInit(Factory_t *pf,int threadNum,int capacity);
int factoryStart(Factory_t *pf);
void destroyFactory(Factory_t *pf);
void *threadUpDown(void *pArg);
int tcp_connect(const char* ip, int port);
#endif
