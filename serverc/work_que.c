#include "work_que.h"

int queInit(pQue_t pq,int capacity)
{
    memset(pq,0,sizeof(Que_t));
    pq->queHead = pq->queTail = NULL;
    pq->capacity = capacity;
    pq->size = 0;
    pthread_mutex_init(&pq->mutex,NULL);
    return 0;
}
unsigned char isQueEmpty(pQue_t pq)
{
    return pq->size == 0;
}
/* 
int queFront(pQue_t pq)
{
    if(isQueEmpty(pq))
        return -1;

    return pq->queHead->socketFd;
}*/
Node_t * quePop(pQue_t pq)
{
    if(isQueEmpty(pq)){
        return NULL;
    }
    pq->size--;
    Node_t *node = pq->queHead;
    pq->queHead= pq->queHead->next;
    if(isQueEmpty(pq))
        pq->queTail=NULL;

    return node;
}
void quePush(pQue_t pq,Node_t *pNode)
{
    pthread_mutex_lock(&pq->mutex);
    if(isQueEmpty(pq)){
        pq->queHead = pq->queTail= pNode;
    }
    else{
        pq->queTail->next= pNode;
        pq->queTail = pNode;
    }
    pq->size++;
    pthread_mutex_unlock(&pq->mutex);
}
void queClear(pQue_t pq)
{
    pthread_mutex_lock(&pq->mutex);
    Node_t *p,*q;
    p=pq->queHead;
    while(p!=pq->queTail){
        q=p;
        p=p->next;
        close(q->socketFd);
        free(q);
    }
    pthread_mutex_unlock(&pq->mutex);
    pthread_mutex_destroy(&pq->mutex);
}
