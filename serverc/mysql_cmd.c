#include "mysql_cmd.h"
#include "head.h"

#define maxConn 5
connPool_t connPool;
int mysqlConnectionPoolInit()
{
    int i=0;
    connPool.capacity=maxConn;
    connPool.size=maxConn;
    pthread_mutex_init(&connPool.mutex,NULL);
    pthread_cond_init(&connPool.cond,NULL);
    connPool.poolHead=connPool.poolTail=NULL;
    for(i=0;i<connPool.capacity;i++){
        MYSQL *conn=(MYSQL *)malloc(sizeof(MYSQL));
        mysql_init(conn);
        if(!mysql_real_connect(conn,MYSQL_IP,MYSQL_USER,MYSQL_PASSWD,MYSQL_DATABASE,0,NULL,0)){
            perror("mysql_real_connect");
            return -1;
        }
        connNode_t *node=(connNode_t *)malloc(sizeof(connNode_t));
        node->conn=conn;
        node->next=NULL;
        connPoolPush(node);
    }
    return 0;
}
connNode_t * connPoolPop()
{
    if(connPool.size==0)
        return NULL;
    connNode_t *node=connPool.poolHead;
    connPool.poolHead=connPool.poolHead->next;
    if(connPool.poolHead==NULL)
        connPool.poolTail=NULL;
    connPool.size--;
    return node;
}
void connPoolPush(connNode_t *node)
{
    pthread_mutex_lock(&connPool.mutex);
    if(connPool.poolHead==NULL){
        connPool.poolHead=connPool.poolTail=node;
    }
    else{
        connPool.poolTail->next=node;
        connPool.poolTail=node;
    }
    connPool.size++;
    pthread_mutex_unlock(&connPool.mutex);
}
void connPoolClear()
{
    connNode_t *node=connPool.poolHead,*p;
    while(node){
        p=node;
        node=node->next;
        mysql_close(p->conn);
        free(p->conn);
        free(p);
    }
}
void cleanUpConnFunc(void *pArg)
{
    pthread_mutex_unlock(&connPool.mutex);
}
connNode_t* getConn()
{
    connNode_t* node;
    while(1)
    {
        pthread_mutex_lock(&connPool.mutex);
        pthread_cleanup_push(cleanUpConnFunc,NULL);
        if(connPool.size==0)
            pthread_cond_wait(&connPool.cond,&connPool.mutex);

        node = connPoolPop();
        pthread_cleanup_pop(1);
        if(node == NULL){
            continue;
        }
        return node;
    }
}
int userSignUp(char *username,char *passwd,char *salt,unsigned int *uid)
{
    connNode_t *node=getConn();
    MYSQL *conn=node->conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[300];
    int k=-1;
    sprintf(query,"insert into userinfo (username,passwd,salt,signuptime,logintime)"
            " values('%s','%s','%s',now(),now())", username,passwd,salt);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) == 0){
        sprintf(query,"select id from userinfo where username='%s'",username);
        printf("%s\n",query);
        if(mysql_query(conn,query) == 0){
            if((res=mysql_use_result(conn))){
                while((row=mysql_fetch_row(res))){
                    k++;
                    *uid=atoi(row[0]);
                }
            }
            mysql_free_result(res);
        }
    }
    connPoolPush(node);
    return k;
}
int userSignIn(char *username,char *passwd,char *salt,unsigned int *uid)
{
    connNode_t *node=getConn();
    MYSQL *conn=node->conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[100];
    int k=0;
    sprintf(query,"select id,salt,passwd from userinfo where username='%s'",username);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) == 0){
        if((res=mysql_use_result(conn))){
           while((row=mysql_fetch_row(res)))
           {
               *uid=atoi(row[0]);
               strcpy(salt,row[1]);
               strcpy(passwd,row[2]);
               k++;
           }
           mysql_free_result(res);
        }
    }
    else{
        connPoolPush(node);
        #ifdef DEBUG_SERVER
        printf("mysql_query error\n");
        #endif
        return -2;
    }
    connPoolPush(node);
    if(k==0)
    {
        printf("no data\n");
        return -1;
    }
    return 0;
}
int updateToken(user_token_t *puserToken)
{
    connNode_t *node=getConn();
    MYSQL *conn=node->conn;
    //INSERT INTO tb_addrbook(num,name,mobile) VALUE('1001','小李','13112345678') 
    //ON DUPLICATE KEY UPDATE name= '小李',mobile='13112345678'
    char query[300];
    sprintf(query,"insert into user_token(uid,user_token,expire_time) value(%d,'%s',unix_timestamp(now()))"
            "ON DUPLICATE KEY UPDATE user_token='%s',expire_time=unix_timestamp(now())",
            puserToken->uid,puserToken->token,puserToken->token);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) == 0){
        connPoolPush(node);
        return 0;
    }
    connPoolPush(node);
    return -1;
}
int getFileList(unsigned int uid,unsigned int dirid,char *buf)
{
    connNode_t *node=getConn();
    MYSQL *conn=node->conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[100];
    sprintf(query,"select type,filesize,filename from userfile where uid=%d and dirid=%d"
            " order by type desc,filename asc",uid,dirid); 
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    int k=0;
    if(mysql_query(conn,query) == 0){
        buf[0]=0;
        if((res=mysql_use_result(conn))){
            while((row=mysql_fetch_row(res))){
                sprintf(buf+k,"%s %sB %s\n",row[0],row[1],row[2]);
                k = strlen(buf);
            }
            if(k>0){
                buf[--k]=0;
            }
            mysql_free_result(res);
        }
        connPoolPush(node);
        return 0;
    }
    connPoolPush(node);
    return -1;
}
int cdDir(unsigned int uid,unsigned int *dirid,char *buf)
{
    connNode_t *node=getConn();
    MYSQL *conn=node->conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[300];
    if(strcmp(buf,"..")==0){
        sprintf(query,"select dirid from userfile where id=%d", *dirid);
    }
    else{
        sprintf(query,"select id from userfile where uid=%d and dirid=%d and type ='d'"
            "and filename='%s'", uid,*dirid,buf); 
    }
    
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    int k=0;
    if(mysql_query(conn,query) == 0){
        if((res=mysql_use_result(conn))){
            if((row=mysql_fetch_row(res)) != NULL){
                *dirid=atoi(row[0]);
                k++;
            }
            mysql_free_result(res);
        }
    }
    connPoolPush(node);
    if(k>0)
        return 0;
    return -1;
}
int mkdirInsql(unsigned int uid,unsigned int dirid,char *buf)
{
    connNode_t *node=getConn();
    MYSQL *conn=node->conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[300];
    int k=-1;
    sprintf(query,"select 1 from userfile where uid=%d and dirid=%d and type='d' and filename='%s'"
            ,uid,dirid,buf);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) == 0){
        if((res=mysql_use_result(conn))){
            if((row=mysql_fetch_row(res)) != NULL){
                k=atoi(row[0]);
            }
            mysql_free_result(res);
        }
    }
    if(k == 1){
        connPoolPush(node);
        return -1;
    }
    sprintf(query,"insert into userfile (uid,dirid,type,filesize,filename,altertime) values"
            "(%d,%d,'d',0,'%s',now())",uid,dirid,buf);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) != 0){
        connPoolPush(node);
        return -1;
    }
    connPoolPush(node);
    return 0;
}
int removeFile(unsigned int uid,unsigned int dirid,char *buf)
{
    connNode_t *node=getConn();
    MYSQL *conn=node->conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[300];
    int fid=-1;
    sprintf(query,"select id from userfile where uid=%d and dirid=%d and type ='-'"
            "and filename='%s'", uid,dirid,buf);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) == 0){
        if((res=mysql_use_result(conn))){
            if((row=mysql_fetch_row(res)) != NULL){
                fid=atoi(row[0]);
            }
            mysql_free_result(res);
        }
    }
    if(fid==-1)//找不到该文件，删除错误
        return -1;
    sprintf(query,"delete from userfile where id=%d", fid);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) != 0){
        connPoolPush(node);
        return -1;
    }
    connPoolPush(node);
    return 0;
}
int removeDir(unsigned int dirid,unsigned int uid,char *buf)
{
    connNode_t *node=getConn();
    MYSQL *conn=node->conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int newid=0;
    char query[300];
    sprintf(query,"select id from userfile where dirid=%d and type ='d' and filename='%s'",dirid,buf);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) == 0){
        if((res=mysql_use_result(conn))){
            while((row=mysql_fetch_row(res)))
                newid=atoi(row[0]);
            mysql_free_result(res);
        }
        if(newid > 0){//remove dir exist
            sprintf(query,"call proc_delete_userfile(%d)",newid);
            if(mysql_query(conn,query) == 0){
                connPoolPush(node);
                return 0;
            }
        }
    }
    connPoolPush(node);
    return -1;
}
/* 
int removeDir(unsigned int uid,unsigned int dirid,char *buf)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    int newid=0,count = -1;
    char query[300];
    sprintf(query,"select id from userfile where dirid=%d and type ='d' and filename='%s'",dirid,buf);
    #ifdef DEBUG_SERVER
    printf("%s\n",buf);
    #endif
    if(mysql_query(conn,query) == 0){
        if((res=mysql_use_result(conn))){
            while((row=mysql_fetch_row(res)))
                newid=atoi(row[0]);
            mysql_free_result(res);
        }
        if(newid > 0){//remove dir exist
            sprintf(query,"select count(id) from userfile where uid=%d and dirid=%d and type ='d'"
                , uid,newid);//remove dir exist have dir?
            if(mysql_query(conn,query) == 0){
                if((res=mysql_use_result(conn))){
                    while((row=mysql_fetch_row(res)))
                        count=atoi(row[0]);
                    mysql_free_result(res);
                }
            }
        }
        if(count == 0){// no dir,delete all file and it self
            sprintf(query,"delete from userfile where (uid=%d and dirid=%d) or id=%d"
                , uid,newid,newid);
            if(mysql_query(conn,query) == 0){
                if((res=mysql_use_result(conn))){
                    mysql_free_result(res);
                }
            }
            return 0;
        }
    }
    return -1;
}*/
int findFileMd5(msg_fileinfo_t *filemd5)
{
    connNode_t *node=getConn();
    MYSQL *conn=node->conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[200];
    int k=0;

    sprintf(query,"select 1 from filemd5 where md5sum ='%s' and filesize=%ld",filemd5->file_md5sum,filemd5->file_size);
    #ifdef DEBUG_SERVER
    printf("findFileMd5 %s\n",filemd5->file_name);
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) == 0){
        if((res=mysql_use_result(conn))){
            while((row=mysql_fetch_row(res))){
                k++;
            }
            mysql_free_result(res);
        }
    }
    else{
        connPoolPush(node);
        #ifdef DEBUG_SERVER
        printf("findFileMd5 error\n");
        #endif
        return -1;
    }
    connPoolPush(node);
    return k;
}
int findFileInfo(unsigned int uid,unsigned int dirid,msg_fileinfo_t *filemd5)
{
    connNode_t *node=getConn();
    MYSQL *conn=node->conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[400];
    int k=0;
    sprintf(query,"select md5sum,filesize from filemd5 where id=(select fid from userfile where uid=%d and dirid=%d and filename ='%s')",
            uid,dirid,filemd5->file_name);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) == 0){
        if((res=mysql_use_result(conn))){
            while((row=mysql_fetch_row(res))){
                sprintf(filemd5->file_md5sum,"%s",row[0]);
                filemd5->file_size=atoi(row[1]);
                k++;
            }
            mysql_free_result(res);
        }
    }
    else{
        connPoolPush(node);
        #ifdef DEBUG_SERVER
        printf("findFileInfo fid sql error\n");
        #endif
        return -2;
    }
    connPoolPush(node);
    if(k==0){
        #ifdef DEBUG_SERVER
        printf("findFileInfo %s no found in database\n",filemd5->file_name);
        #endif
        return 0;
    }
    return 1;
}
int insertFileInfo(unsigned int uid,unsigned int dirid,msg_fileinfo_t *filemd5)
{
    connNode_t *node=getConn();
    MYSQL *conn=node->conn;
    char query[500];
    sprintf(query,"insert into userfile(uid,dirid,type,fid,filesize,filename,altertime)"
            "select %d,%d,'-',id,%ld,'%s',now() from filemd5 where md5sum='%s'"
            ,uid,dirid,filemd5->file_size,filemd5->file_name,filemd5->file_md5sum);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) != 0){
        connPoolPush(node);
        #ifdef DEBUG_SERVER
        printf("insertFile 2 sql error\n");
        #endif
        return -1;
    }
    connPoolPush(node);
    return 0;
}
