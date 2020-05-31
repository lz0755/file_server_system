#include "common.h"

#define MYSQL_IP "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWD "123456"
#define MYSQL_DATABASE "baidudisk"

int mysqlInit();
int insertFileMd5(msg_fileinfo_t *filemd5);
int insertFileInfo(unsigned int uid,unsigned int dirid,msg_fileinfo_t *filemd5);
int findFileMd5(msg_fileinfo_t *filemd5);
int updateToken(user_token_t *puserToken);
int tokenIndentification(user_token_t *puserToken);