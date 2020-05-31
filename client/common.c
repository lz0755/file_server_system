#include "common.h"
#include "head.h"
#include "openssl_md5.h"

extern int ftruncate(int fd, off_t length);

int sendCmd(int fd,cmd_t *pcmd,int type,int len)
{
    pcmd->type=type;
    pcmd->len=len;
    int ret = send(fd,pcmd,CMD_HEAD_LEN+pcmd->len,0);
    #ifdef DEBUF_CLIENT
    printf("send %d\n",ret);
    #endif
    return ret;
}
void sendAckCmd(int fd,cmd_t *pcmd,int type)
{
    pcmd->type=type;
    pcmd->len=0;
    int ret = send(fd,pcmd,CMD_HEAD_LEN+pcmd->len,0);
    printf("send=%d ack %d\n",ret,type);
}
int recvCmd(int socketFd,cmd_t *pcmd)
{
    int ret;
    ret = recv(socketFd,pcmd,CMD_HEAD_LEN,MSG_WAITALL);
    ERROR_CHECK(ret,-1,"recv");
    if(ret == 0)
        return -2;
    #ifdef DEBUF_CLIENT
    printf("recvCmd ret=%d len=%d type=%d\n",ret,pcmd->len,pcmd->type);
    #endif
    pcmd->buf[pcmd->len]=0;
    if(pcmd->len == 0)
        return 0;
    ret = recv(socketFd,pcmd->buf,pcmd->len,MSG_WAITALL);
    ERROR_CHECK(ret,-1,"recv");
    if(ret == 0)
        return -2;
    pcmd->buf[pcmd->len]=0;
    return 0;
}

int recvFile(int socketFd,char flag,msg_fileinfo_t *pfileInfo,int type)
{
    cmd_t cmd;
    #ifdef DEBUF_CLIENT
    printf("filename:%s  file_chunk_size:%ld offset %ld filesize %ld md5 %s\n",
            pfileInfo->file_name,pfileInfo->file_chunk_size,pfileInfo->offset,pfileInfo->file_size,pfileInfo->file_md5sum);
    #endif
    int fd;
    if(flag=='0'){//client
        fd=open(pfileInfo->file_name,O_RDWR|O_CREAT,0666);
    }
    else{//server
        fd=open(pfileInfo->file_md5sum,O_RDWR|O_CREAT,0666);
    }
    if(fd ==-1){
        perror("open");
        cmd.buf[0]='0';
        sendCmd(socketFd,&cmd,type,1);//3发送信息表示失败
        return -1;
    }
    //printf("fd=%d",fd);
    cmd.buf[0]='1';
    sendCmd(socketFd,&cmd,type,1);//3发送信息表示开始接收文件
    memcpy(cmd.buf,pfileInfo,sizeof(msg_fileinfo_t));
    sendCmd(socketFd,&cmd,cmd.type,sizeof(msg_fileinfo_t));//4发送文件信息
    //5开始接收文件
    int ret;
    //long sliceSize=pfileInfo->file_chunk_size/100,oldRecvLen=0;
    long recvLen=0;
    //printf("chunk:%ld  ",pfileInfo->offset/pfileInfo->file_chunk_size);
    lseek(fd,pfileInfo->offset,SEEK_SET);
    while(recvLen<pfileInfo->file_chunk_size)
    {
        if(pfileInfo->file_chunk_size-recvLen >= 1000)
            ret = recv(socketFd,cmd.buf,1000,MSG_WAITALL);
        else
            ret = recv(socketFd,cmd.buf,pfileInfo->file_chunk_size-recvLen,MSG_WAITALL);
        if(ret==-1 || ret == 0){
            close(fd);
            return -2;
        }
        write(fd,cmd.buf,ret);
        recvLen += ret;

    }
    close(fd);
    //printf("success\n");
    return 0; 
}

int sendFile(int socketFd,char flag,msg_fileinfo_t *pfileInfo,long offset,int type)
{
    cmd_t cmd;
    int fd;
    pfileInfo->offset = offset;
    if(flag=='0'){
        fd=open(pfileInfo->file_name,O_RDONLY);
    }
    else{
        fd=open(pfileInfo->file_md5sum,O_RDONLY);
    }
    if(fd ==-1){
        perror("open");
        cmd.buf[0]='0';
        sendCmd(socketFd,&cmd,type,1);//3发送信息表示失败
        return -1;
    }
    cmd.buf[0]='1';
    sendCmd(socketFd,&cmd,type,1);//3发送信息表示开始发送文件

    memcpy(cmd.buf,pfileInfo,sizeof(msg_fileinfo_t));
    cmd.len=MSG_FILEINFO_HEAD_LEN+strlen(pfileInfo->file_name)+1;
    #ifdef DEBUF_CLIENT
    printf("send filename:%s  filesize:%ld offset %ld md5 %s\n",
            pfileInfo->file_name,pfileInfo->file_size,pfileInfo->offset,pfileInfo->file_md5sum);
    #endif
    int ret = sendCmd(socketFd,&cmd,type,cmd.len);//4发送文件信息
    //ERROR_CHECK(ret,-1,"send");
    // recvCmd(socketFd,&cmd);//recv confirm
    // printf("recv confirm\n");
    // if(cmd.buf[0]!='0')
    //     return 0;
    //printf("start send file\n");
    ret = sendfile(socketFd,fd,&offset,pfileInfo->file_size-offset);//5发送文件
    close(fd);
    //printf("sendfile %d\n",ret);
    ERROR_CHECK(ret,-1,"sendfile");
    printf("success\n");
    return 0;
} 
