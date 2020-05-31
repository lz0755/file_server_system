#include "common.h"
#include <mysql/mysql.h>

#define MYSQL_IP "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWD "123456"
#define MYSQL_DATABASE "baidudisk"

typedef struct conn_node{
    MYSQL *conn;
    struct conn_node *next;
}connNode_t;

typedef struct{
    connNode_t *poolHead,*poolTail;
    int capacity;
    int size;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}connPool_t;

int mysqlConnectionPoolInit();
//connNode_t * connPoolFront(pconnPool_t pq);
connNode_t * connPoolPop();
void connPoolPush(connNode_t *);
void connPoolClear();
void cleanUpConnFunc(void *pArg);

//int getSaltFromMysql(char *username);
int userSignIn(char *username,char *passwd,char *salt,unsigned int *uid);
int userSignUp(char *username,char *passwd,char *salt,unsigned int *uid);
int getFileList(unsigned int uid,unsigned int dirid,char *buf);
int mkdirInsql(unsigned int uid,unsigned int dirid,char *buf);
int removeFile(unsigned int uid,unsigned int dirid,char *buf);
int removeDir(unsigned int uid,unsigned int dirid,char *buf);
int cdDir(unsigned int uid,unsigned int *dirid,char *buf);
int insertFileInfo(unsigned int uid,unsigned int dirid,msg_fileinfo_t *filemd5);
int insertFileMd5(msg_fileinfo_t *filemd5);
int findFileMd5(msg_fileinfo_t *filemd5);
int findFileInfo(unsigned int uid,unsigned int dirid,msg_fileinfo_t *filemd5);
int updateToken(user_token_t *puserToken);