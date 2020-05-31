#ifndef __WORK_QUE__
#define __WORK_QUE__
#include "head.h"
#include "common.h"
typedef struct tag_node{
    msg_fileinfo_t fileinfo;
    char ip[32];
    int port;
    struct tag_node *next;
}Node_t,*pNode_t;

typedef struct{
    pNode_t queHead,queTail;
    int capacity;
    int size;
    pthread_mutex_t mutex;
}Que_t,*pQue_t;
int queInit(pQue_t pq,int capacity);
//Node_t * queFront(pQue_t pq);
Node_t * quePop(pQue_t pq);
void quePush(pQue_t pq,Node_t *);
void queClear(pQue_t pq);
unsigned char isQueEmpty(pQue_t pq);
#endif
