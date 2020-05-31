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

int recvFile(int socketFd,msg_fileinfo_t *pfileInfo)
{
    cmd_t cmd;
    recvCmd(socketFd,&cmd);//4接收文件信息
    memcpy(pfileInfo,cmd.buf,cmd.len);
    #ifdef DEBUG_SERVER
    printf("filename:%s  filesize:%ld offset %ld md5 %s\n",
            pfileInfo->file_name,pfileInfo->file_size,pfileInfo->offset,pfileInfo->file_md5sum);
    #endif
    int fd;
    fd=open(pfileInfo->file_md5sum,O_RDWR|O_CREAT,0666);
    
    if(fd==-1) {
        #ifdef DEBUG_SERVER
        printf("errno=%d,\n",errno);perror("open");
        #endif
        return -1;
    }
    ftruncate(fd,pfileInfo->file_size);
    char *pMap=(char*)mmap(NULL,pfileInfo->file_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(pMap == (char*)-1){
        close(fd);
        perror("mmap");
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
            ret = recv(socketFd,pMap+recvLen,1000,MSG_WAITALL);
        else
            ret = recv(socketFd,pMap+recvLen,pfileInfo->file_size-recvLen,MSG_WAITALL);
        if(ret==-1 || ret == 0){
            close(fd);
            ret=munmap(pMap,pfileInfo->file_size);
            if(ret == -1){
                perror("munmap");
            }
            return -2;
        }
        //write(fd,cmd.buf,ret);
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
    ret=munmap(pMap,pfileInfo->file_size);
    if(ret == -1){
        perror("munmap");
        return -1;
    }
    #ifdef DEBUG_SERVER
    printf("success\n");
    #endif
    return 0; 
}

int sendFile(int socketFd)
{
    cmd_t cmd;
    recvCmd(socketFd,&cmd);//4接收文件信息
    msg_fileinfo_t *pfileInfo=(msg_fileinfo_t *)cmd.buf;
    int fd;
    fd=open(pfileInfo->file_md5sum,O_RDWR);    

    if(fd==-1) {
        #ifdef DEBUG_SERVER
        printf("errno=%d,\n",errno);perror("open");
        #endif
        return -1;
    }

    #ifdef DEBUG_SERVER
    printf("send filename:%s  filesize:%ld offset %ld md5 %s  chunksize:%ld\n",
            pfileInfo->file_name,pfileInfo->file_size,pfileInfo->offset,pfileInfo->file_md5sum,pfileInfo->file_chunk_size);
    #endif
    int ret;

    #ifdef DEBUG_SERVER
    printf("start send file\n");
    #endif
    //5发送文件
    ret = sendfile(socketFd,fd,&pfileInfo->offset,pfileInfo->file_chunk_size);
    //lseek(socketFd,pfileInfo->offset,SEEK_SET);
    // char *pMap=(char*)mmap(NULL,pfileInfo->file_chunk_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,pfileInfo->offset);
    // if(pMap == (char*)-1){
    //     close(fd);
    //     perror("mmap");
    //     return -1;
    // }
    // ret = send(socketFd,pMap,pfileInfo->file_chunk_size,0);
    #ifdef DEBUG_SERVER
    printf("sendfile %d\n",ret);
    #endif
    if(ret==-1) {
        #ifdef DEBUG_SERVER
        printf("errno=%d,\n",errno);perror("sendfile");
        #endif
        close(fd);
        return -2;
    }
    close(fd);
    return 0;
} 
