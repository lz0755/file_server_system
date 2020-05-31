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
int SignCmd(int newFd,char *username,user_token_t *userToken,cmd_t *pcmd)
{
    
    char passwd[120];
    char salt[12];
    int ret;
    if(pcmd->type == LOGIN){
        strcpy(username,pcmd->buf);
        if(userSignIn(username,passwd,salt,&userToken->uid) == 0)
        {
            //printf("passwd %s\n",passwd);
            strcpy(pcmd->buf,salt);
            //send salt
            sendCmd(newFd,pcmd,LOGINSUCC,sizeof(salt));
            //recv passwd
            ret = recvCmd(newFd,pcmd);
            if(ret != 0)
                return -2;

            //printf("recv passwd %s\n",pcmd->buf);
            if(strcmp(passwd,pcmd->buf) == 0){
                sendCmd(newFd,pcmd,LOGINSUCC,0);
            }
            else{
                sendCmd(newFd,pcmd,LOGINFAIL,0);
                return -1;
            }
        }
        else{
            sendCmd(newFd,pcmd,LOGINFAIL,0);
            return -1;
        }
    }
    else{
        #ifdef DEBUG_SERVER
        printf("sign up\n");
        #endif
        getSalt(salt,11);
        //printf("salt %s\n",salt);
        memcpy(pcmd->buf,salt,11);
        sendCmd(newFd,pcmd,SIGNUP,11);//发送盐值
        ret = recvCmd(newFd,pcmd);//等待客户端回复用户名和加密后的密码
        if(ret != 0){
            return -2;
        }
        sscanf(pcmd->buf,"%s %s",username,passwd);
        if(userSignUp(username,passwd,salt,&userToken->uid) == 0)
        {
            sendCmd(newFd,pcmd,SIGNUPSUCC,0);
        }
        else{
            #ifdef DEBUG_SERVER
            printf("sign up error:%s\n",username);
            #endif
            sendCmd(newFd,pcmd,SIGNUPFAIL,0);
            return -1;
        }
    }
    char temp[200];
    char tstr[100];
    time_t t;
    time(&t);
    ctime_r(&t,tstr);
    sprintf(temp,"%s%d%s%s",username,userToken->uid,passwd,tstr);
    Compute_string_md5(temp,userToken->token);
    updateToken(userToken);
    memcpy(pcmd->buf,userToken,sizeof(user_token_t));
    sendCmd(newFd,pcmd,TOKEN,sizeof(user_token_t));

    return 0;
}
void autoUpdateToken(user_token_t *userToken)
{
    updateToken(userToken);
}
int cdCmd(int newFd,unsigned int uid,unsigned int *curDirId,cmd_t *pcmd)
{
    if(strcmp(pcmd->buf,"/")==0){
        *curDirId=0;
        return 0;
    }
    return cdDir(uid,curDirId,pcmd->buf);
}
void lsCmd(int newFd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd)
{
    int ret=getFileList(uid,curDirId,pcmd->buf);
    if(ret == 0)
        sendCmd(newFd,pcmd,LS,strlen(pcmd->buf));
}
int mkdirCmd(int newFd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd)
{
    return mkdirInsql(uid,curDirId,pcmd->buf);
}
int removeCmd(int newFd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd)
{
    return removeFile(uid,curDirId,pcmd->buf);
}
int rmdirCmd(int newFd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd)
{
    return removeDir(curDirId,uid,pcmd->buf);
}

int putsCmd(int newFd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd)
{
    msg_fileinfo_t filemd5;
    memcpy(&filemd5,pcmd->buf,pcmd->len);
    int ret=findFileMd5(&filemd5);
    if(ret == -1){//2数据库查询失败
        pcmd->buf[0]='0';
        sendCmd(newFd,pcmd,PUTS,1);
        return -1;
    }
    if(ret == 1){
        //2数据库中已存在该文件信息，秒传
        insertFileInfo(uid,curDirId,&filemd5);
        pcmd->buf[0]='1';
        sendCmd(newFd,pcmd,PUTS,1);
        return 0;
    }
    //3传送服务器信息
    sprintf(pcmd->buf,"%s %d","192.168.5.199",6667);
    printf("%s\n",pcmd->buf);
    sendCmd(newFd,pcmd,PUTS,strlen(pcmd->buf));
    return 0;
}
int getsCmd(int newFd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd)
{
    long offset=0;
    msg_fileinfo_t fileinfo;
    if(pcmd->type==GETS2){
        sscanf(pcmd->buf,"%s %ld",fileinfo.file_name,&offset);
    }
    else
    {
        strcpy(fileinfo.file_name,pcmd->buf);
    }
 
    int ret =findFileInfo(uid,curDirId,&fileinfo);
    if(ret == -1){//数据库查询失败
        pcmd->buf[0]='2';
        sendCmd(newFd,pcmd,GETS,1);
        return -1;
    }
    if(ret == 0){
        pcmd->buf[0]='0';//数据库中不存在该文件信息
        sendCmd(newFd,pcmd,GETS,1);
        return 0;
    }
    //数据库中已存在该文件信息，传送服务器信息
    pcmd->len=MSG_FILEINFO_HEAD_LEN+strlen(fileinfo.file_name);
    memcpy(pcmd->buf,&fileinfo,pcmd->len);
    sendCmd(newFd,pcmd,GETS,pcmd->len);
    sprintf(pcmd->buf,"%s %d","192.168.5.199",6667);
    sprintf(pcmd->buf+25,"%s %d","192.168.5.199",6668);
    sprintf(pcmd->buf+50,"%s %d","192.168.5.199",6669);
    sendCmd(newFd,pcmd,GETS,75);
    //sendFile(newFd,'1',&fileinfo,offset,GETS);
    return 0;
}