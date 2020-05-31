#include "mysql_cmd.h"
#include "head.h"
#include <mysql/mysql.h>
MYSQL *conn;
int mysqlInit()
{
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,MYSQL_IP,MYSQL_USER,MYSQL_PASSWD,MYSQL_DATABASE,0,NULL,0)){
        perror("mysql_real_connect");
        return -1;
    }
    return 0;
}
int tokenIndentification(user_token_t *puserToken)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[200];
    int k=0;//token保持10分钟有效期
    sprintf(query,"select 1 from user_token where uid=%d and user_token='%s' and expire_time+600>unix_timestamp(now())",
            puserToken->uid,puserToken->token);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) == 0){
        if((res=mysql_use_result(conn))){
            while((row=mysql_fetch_row(res))){
                k=atoi(row[0]);
            }
            mysql_free_result(res);
        }
        if(k==1)
            return 0;
    }
    return -1;
}
int updateToken(user_token_t *puserToken)
{
    //INSERT INTO tb_addrbook(num,name,mobile) VALUE('1001','小李','13112345678') 
    //ON DUPLICATE KEY UPDATE name= '小李',mobile='13112345678'
    char query[200];
    sprintf(query,"insert into user_token(uid,user_token,expire_time) value(%d,'%s',unix_timestamp(now()))",
            puserToken->uid,puserToken->token);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) == 0){
        return 0;
    }
    return -1;
}
int insertFileInfo(unsigned int uid,unsigned int dirid,msg_fileinfo_t *filemd5)
{
    char query[500];
    sprintf(query,"insert into userfile(uid,dirid,type,fid,filesize,filename,altertime)"
            "select %d,%d,'-',id,%ld,'%s',now() from filemd5 where md5sum='%s'"
            ,uid,dirid,filemd5->file_size,filemd5->file_name,filemd5->file_md5sum);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) != 0){
        #ifdef DEBUG_SERVER
        printf("insertFile 2 sql error\n");
        #endif
        return -1;
    }
    return 0;
}
int insertFileMd5(msg_fileinfo_t *filemd5)
{
    char query[500];
    sprintf(query,"insert into filemd5(refcount,filesize,md5sum) values(1,%ld,'%s')",
            filemd5->file_size,filemd5->file_md5sum);
    #ifdef DEBUG_SERVER
    printf("%s\n",query);
    #endif
    if(mysql_query(conn,query) != 0){
        printf("insertFile 1sql error\n");
        return -1;
    }
    return 0;
}