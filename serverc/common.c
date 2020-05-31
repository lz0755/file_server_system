#include "common.h"
#include "head.h"
#include "openssl_md5.h"

const char cmdtext[][20]={
    "","cd","ls","mkdir","rmdir","puts","gets","gets again","remove","pwd","exit",
    "login","login success","login failed","other"
};
extern int ftruncate(int fd, off_t length);

int sendCmd(int fd,cmd_t *pcmd,int type,int len)
{
    pcmd->type=type;
    pcmd->len=len;
    int ret = send(fd,pcmd,CMD_HEAD_LEN+pcmd->len,0);
    #ifdef DEBUG_SERVER
    printf("send %d  cmd=%d\n",ret,type);
    #endif
    return ret;
}
void sendAckCmd(int fd,cmd_t *pcmd,int type)
{
    pcmd->type=type;
    pcmd->len=0;
    int ret = send(fd,pcmd,CMD_HEAD_LEN+pcmd->len,0);
    #ifdef DEBUG_SERVER
    printf("send=%d ack %d\n",ret,type);
    #endif
}
int recvCmd(int socketFd,cmd_t *pcmd)
{
    int ret;
    ret = recv(socketFd,pcmd,CMD_HEAD_LEN,MSG_WAITALL);
    if(ret==-1) {
        #ifdef DEBUG_SERVER
        printf("errno=%d,\n",errno);perror("recv");
        #endif
        return -1;
    }
    if(ret == 0)
        return -2;
    #ifdef DEBUG_SERVER
    printf("recvCmd ret=%d len=%d type=%d\n",ret,pcmd->len,pcmd->type);
    if(pcmd->type > OTHER)
        return -1;
    #endif
    pcmd->buf[pcmd->len]=0;
    if(pcmd->len == 0)
        return 0;
    ret = recv(socketFd,pcmd->buf,pcmd->len,MSG_WAITALL);
    if(ret==-1) {
        #ifdef DEBUG_SERVER
        printf("errno=%d,\n",errno);perror("recv");
        #endif
        return -1;
    }
    if(ret == 0)
        return -2;
    pcmd->buf[pcmd->len]=0;
    return 0;
}

int recvFile(int socketFd,char flag,msg_fileinfo_t *pfileInfo)
{
    cmd_t cmd;
    #ifdef DEBUG_SERVER
    printf("filename:%s  filesize:%ld offset %ld md5 %s\n",
            pfileInfo->file_name,pfileInfo->file_size,pfileInfo->offset,pfileInfo->file_md5sum);
    #endif
    int fd;
    if(flag=='0'){//client
        fd=open(pfileInfo->file_name,O_RDWR|O_CREAT|O_APPEND,0666);
    }
    else{//server
        fd=open(pfileInfo->file_md5sum,O_RDWR|O_CREAT|O_APPEND,0666);
    }
    
    if(fd==-1) {
        #ifdef DEBUG_SERVER
        printf("errno=%d,\n",errno);perror("open");
        #endif
        return -1;
    }
    int ret;
    #ifdef DEBUG_SERVER
    long sliceSize=pfileInfo->file_size/100,oldRecvLen=0;
    #endif
    long recvLen=pfileInfo->offset;

    while(recvLen<pfileInfo->file_size)
    {
        if(pfileInfo->file_size-recvLen >= 1000)
            ret = recv(socketFd,cmd.buf,1000,MSG_WAITALL);
        else
            ret = recv(socketFd,cmd.buf,pfileInfo->file_size-recvLen,MSG_WAITALL);
        if(ret==-1 || ret == 0){
            close(fd);
            return -2;
        }
        write(fd,cmd.buf,ret);
        recvLen += ret;
        #ifdef DEBUG_SERVER
        if(recvLen == pfileInfo->file_size){
            printf("100%%\n");
            break;
        }
        else if(recvLen - oldRecvLen > sliceSize){
            printf("%2.2lf%%\r",(double)recvLen/pfileInfo->file_size*100);
            oldRecvLen = recvLen;
            fflush(stdout);
        }
        #endif
    }
    close(fd);
    #ifdef DEBUG_SERVER
    printf("success\n");
    #endif
    return 0; 
}

int sendFile(int socketFd,char flag,msg_fileinfo_t *pfileInfo,long offset,int type)
{
    cmd_t cmd;
    int fd;
    pfileInfo->offset = offset;
    if(flag=='0'){
        Compute_file_md5(pfileInfo->file_name,pfileInfo->file_md5sum);
        fd=open(pfileInfo->file_name,O_RDONLY);
        if(fd==-1) {
            #ifdef DEBUG_SERVER
            printf("errno=%d,\n",errno);perror("open");
            #endif
            return -1;
        }
        struct stat buf;
        fstat(fd,&buf);
        //copy recv filename
        pfileInfo->file_size = buf.st_size;
    }
    else{
        fd=open(pfileInfo->file_md5sum,O_RDONLY);
        if(fd==-1) {
            #ifdef DEBUG_SERVER
            printf("errno=%d,\n",errno);perror("open");
            #endif
            return -1;
        }
    }
    memcpy(cmd.buf,pfileInfo,sizeof(msg_fileinfo_t));
    cmd.len=MSG_FILEINFO_HEAD_LEN+strlen(pfileInfo->file_name)+1;
    #ifdef DEBUG_SERVER
    printf("send filename:%s  filesize:%ld offset %ld md5 %s\n",
            pfileInfo->file_name,pfileInfo->file_size,pfileInfo->offset,pfileInfo->file_md5sum);
    #endif
    int ret = sendCmd(socketFd,&cmd,type,cmd.len);//send fileinfo

    recvCmd(socketFd,&cmd);//recv confirm
    #ifdef DEBUG_SERVER
    printf("recv confirm\n");
    #endif
    if(cmd.buf[0]!='0')
        return 0;
    #ifdef DEBUG_SERVER
    printf("start send file\n");
    #endif
    if(pfileInfo->file_size < SIZE_100MB){
        ret = sendfile(socketFd,fd,&offset,pfileInfo->file_size-offset);
        #ifdef DEBUG_SERVER
        printf("sendfile %d\n",ret);
        #endif
        if(ret==-1) {
            #ifdef DEBUG_SERVER
            printf("errno=%d,\n",errno);perror("sendfile");
            #endif
            close(fd);
            return -1;
        }
    }
    else{
        lseek(fd,offset,SEEK_SET);
        while((cmd.len = read(fd,cmd.buf,sizeof(cmd.buf))))
        {
            ret = send(socketFd,cmd.buf,cmd.len,0);
            if(ret==-1){
                #ifdef DEBUG_SERVER
                perror("send");
                #endif
                close(fd);
                return -2;
            }
        }
    }
    close(fd);
    return 0;
} 
