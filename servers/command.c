#include "head.h"
#include "command.h"
#include "mysql_cmd.h"
#include "openssl_md5.h"

void getSalt(char *salt,int len)
{
    int i,j;
    salt[0]='$';
    salt[1]='6';
    salt[2]='$';
    srand((unsigned int)time(NULL));
    for(i=3;i<len;i++){
        j=rand()%3;
        if(j==0){
            salt[i]=rand()%26 + 'A';
        }
        else if(j==1){
            salt[i]=rand()%26 + 'a';
        }
        else
        {
            salt[i]=rand()%10+'0';
        }
    }
    salt[len]=0;
}
int tokenCmd(int newFd,user_token_t *userToken,cmd_t *pcmd)
{
    int ret=tokenIndentification(userToken);
    if(ret == -1){
        #ifdef DEBUG_SERVER
        printf("token indentification failed\n");
        #endif
        pcmd->buf[0]='0';
        sendCmd(newFd,pcmd,TOKEN,1);//2发送token确认信息
        return -1;
    }
    #ifdef DEBUG_SERVER
    printf("token indentification success\n");
    #endif
    pcmd->buf[0]='1';
    sendCmd(newFd,pcmd,TOKEN,1);//2发送token确认信息
    return 0;
}


int putsCmd(int newFd,unsigned int uid,cmd_t *pcmd)
{
    msg_fileinfo_t filemd5;
    int ret = recvFile(newFd,&filemd5);
    if(ret != 0)
        return ret;
    recvCmd(newFd,pcmd);
    struct uint_t id;
    memcpy(&id,pcmd->buf,sizeof(id));
    insertFileMd5(&filemd5);
    insertFileInfo(uid,id.uint32,&filemd5);
    return 0;
}
int getsCmd(int newFd,unsigned int uid)
{
    int ret;
    ret = sendFile(newFd);
    return ret;
}