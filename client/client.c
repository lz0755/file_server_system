#include "head.h"
#include "client.h"
#include "openssl_md5.h"
#include "config.h"
extern int lstat(const char *pathname, struct stat *statbuf);
extern int ftruncate(int fd, off_t length);
int main(int argc,char* argv[])
{
    int ret = initConfig();
    if(ret ==-1){
        printf("config file error\n");
        return -1;
    }
    char *ip,*port;
    ip=getConfig("server_ip");
    port=getConfig("server_port");
    if(ip==NULL || port==NULL){
        printf("config doesnot exist\n");
        return -1;
    }
    int socketFd;
    socketFd = tcp_connect(ip,atoi(port));
    if(socketFd == -1)
        return -1;
    char buf[128];

    fd_set rdset;
    int readyFdCount=0;
    cmd_t cmd;
    char username[50];
    char salt[13];
    char curDir[500];
    curDir[0]='/';
    curDir[1]=0;
    //int newFd = tcp_connect(argv[1],atoi(argv[2]));
    Factory_t mainFactory;
    factoryInit(&mainFactory,MAX_THREAD,INIT_CAPACITY);
    factoryStart(&mainFactory);
    //login
    while(1){
        printf("1.Sign up    2.Log in : ");
        fflush(stdout);
        read(STDIN_FILENO,cmd.buf,sizeof(cmd.buf)-1);

        //注册
        if(cmd.buf[0]=='1'){
            printf("sign up username:");
            fflush(stdout);
            memset(cmd.buf,0,sizeof(cmd.buf));
            read(STDIN_FILENO,cmd.buf,sizeof(cmd.buf)-1);
            int len=strlen(cmd.buf)-1;
            if(cmd.buf[0]=='\n' || len < 3 || len > 40){
                printf("username 3-40 character\n");
                continue;
            }
            strcpy(username,cmd.buf);
            char *passwd=getpass("input password:");
            if(passwd[0]=='\n')
                continue;
            //send signup，先发送注册申请
            sendCmd(socketFd,&cmd,SIGNUP,0);
            //recv salt，返回盐值
            recvCmd(socketFd,&cmd);
            char *temp=crypt(passwd,cmd.buf);
            printf("passwd %s\n",temp);
            sprintf(cmd.buf,"%s %s",username,temp);
            printf("%s\n",cmd.buf);
            //send username password，发送加密后的密码和用户名
            sendCmd(socketFd,&cmd,SIGNUP,strlen(cmd.buf));
            recvCmd(socketFd,&cmd);//等待服务器确认
            if(cmd.type==SIGNUPSUCC){
                break;
            }
            else
                printf("sign up error\n");
        }
        else{//登录
            printf("username:");
            fflush(stdout);
            memset(cmd.buf,0,sizeof(cmd.buf));
            read(STDIN_FILENO,cmd.buf,sizeof(cmd.buf)-1);
            if(cmd.buf[0]=='\n')
                continue;
            int len=strlen(cmd.buf)-1;
            //cmd.buf[len]=0;
            //printf("len=%d  %s\n",len,cmd.buf);
            //send username
            sendCmd(socketFd,&cmd,LOGIN,len);
            //recv salt
            recvCmd(socketFd,&cmd);
            if(cmd.type==LOGINSUCC){
                char *passwd=getpass("input password:");
                if(passwd[0]=='\n')
                    continue;
                strcpy(salt,cmd.buf);
                char *temp=crypt(passwd,salt);
                strcpy(cmd.buf,temp);
                //send passwd
                sendCmd(socketFd,&cmd,LOGIN,strlen(cmd.buf));
                recvCmd(socketFd,&cmd);
                if(cmd.type==LOGINSUCC)
                    break;
                else
                    printf("password error\n");
            }
            else
                printf("username error\n");
        }
    }
    system("clear");
    usage();
    //printf("login success\n");
    recvCmd(socketFd,&cmd);
    memcpy(&mainFactory.userToken,cmd.buf,sizeof(user_token_t));
    mainFactory.curDirId=0;
    //printf("uid=%d,token=%s\n",mainFactory.userToken.uid,mainFactory.userToken.token);
    msg_fileinfo_t fileinfo;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(socketFd,&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        readyFdCount = select(socketFd+1,&rdset,NULL,NULL,NULL);
        if(readyFdCount>0)
        {
            if(FD_ISSET(socketFd,&rdset)){
                ret = serverData(socketFd,&mainFactory,&cmd,curDir,&fileinfo);
                if(ret==-1){
                    printf("server disconnect\n");
                    break;
                }
            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                memset(buf,0,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf)-1);

                
                if(buf[0]=='\n'){
                    printf("%s$ ",curDir);
                    fflush(stdout);
                    continue;
                }
                cmd.len=0;
                commandAnalyze(buf,&cmd,curDir);
                if(cmd.type == CD){
                    if(strcmp(cmd.buf,".")==0){
                        printf("%s$ ",curDir);
                        fflush(stdout);
                        continue;
                    }
                }
                if(cmd.type == PWD){
                    printf("%s$ ",curDir);
                    fflush(stdout);
                    continue;
                }
                //printf("cmd:%d %s\n",cmd.type,cmd.buf);
                if(cmd.type == OTHER){
                    printf("command error\n");
                    printf("%s$ ",curDir);
                    fflush(stdout);
                    continue;
                }
                if(cmd.type == PUTS){
                    memcpy(&fileinfo,cmd.buf,cmd.len);
                    printf("send filename:%s  filesize:%ld offset %ld md5 %s\n",
                        fileinfo.file_name,fileinfo.file_size,fileinfo.offset,fileinfo.file_md5sum);
                }
                //printf("send:%d %s\n",cmd.type,cmd.buf);
                send(socketFd,&cmd,CMD_HEAD_LEN+cmd.len,0);

                if(cmd.type == EXIT)
                    break;
                //printf("send cmd ret=%d\n",ret);
            }
        }
    }
    close(socketFd);
    return 0;
}
void usage()
{
    printf(
        "1.cd       进入对应目录\n"
        "2.ls       列出相应目录文件\n"
        "3.puts     将本地文件上传至服务器\n"
        "4.gets     下载服务器文件到本地\n"
        "5.rm       删除服务器上文件\n"
        "6.pwd      显示目前所在路径\n"
        "7.mkdir    下载服务器文件到本地\n"
        "8.rmdir    删除服务器上目录件\n"
        "9.其他命令不响应\n\n\n");
}
int serverData(int socketFd,Factory_t *pf,cmd_t *pcmd,char *curDir,msg_fileinfo_t *pfileInfo)
{
    int ret;
    ret = recvCmd(socketFd,pcmd);
    if(ret != 0)
        return -1;
    //printf("recv len %d cmd %s\n",ret,pcmd->buf);
    switch(pcmd->type)
    {
        case CD:
        {
            if(pcmd->buf[0]=='0'){
                cutDir(curDir);
                printf("dir not exist\n");
            }
            else{
                struct uint_t id;
                memcpy(&id,pcmd->buf+1,sizeof(id));
                pf->curDirId=id.uint32;
                //printf("dirid=%d\n",pf->curDirId);
            }
        }break;
        case MKDIR:
        case RMDIR:
        case REMOVE:
            if(pcmd->buf[0]=='1')
                printf("sucess\n");
            else
                printf("failed\n");
            break;
        case LS: if(pcmd->len > 0) printf("%s\n",pcmd->buf);break;
        case PUTS:
        {
            if(pcmd->len == 1){//2文件存在则秒传
                if(pcmd->buf[0]=='1') printf("puts success\n");
                else  printf("server error\n");
            }
            else
                putsCmd(socketFd,pf,pcmd,pfileInfo);
        } break;
        case GETS:
        case GETS2: 
        {
            if(pcmd->len == 1){
                printf("gets failed\n");
                break;
            }
            getsCmd(socketFd,pf,pcmd);
        } break;
        case OTHER:printf("command error\n");break;
        default:break;
    }
    printf("%s$ ",curDir);
    fflush(stdout);
    return 0;
}
void putsCmd(int socketFd,Factory_t *pf,cmd_t *pcmd,msg_fileinfo_t *pfileInfo)
{
    printf("%s\n",pcmd->buf);
    pf->cmdType=pcmd->type;//3接收文件服务器信息
    Node_t *node=(Node_t *)malloc(sizeof(Node_t));
    node->next=NULL;
    memcpy(&node->fileinfo,pfileInfo,sizeof(msg_fileinfo_t));
    sscanf(pcmd->buf,"%s %d",node->ip,&node->port);
    quePush(&pf->que,node);
    pthread_cond_signal(&pf->cond);
}
void getsCmd(int socketFd,Factory_t *pf,cmd_t *pcmd)
{
    pf->cmdType=pcmd->type;
    int fileServerNum=3;
    long chunkSize;
    //接收文件信息
    msg_fileinfo_t fileinfo;
    memset(&fileinfo,0,sizeof(msg_fileinfo_t));
    memcpy(&fileinfo,pcmd->buf,pcmd->len);
    if(fileinfo.file_size < 1024*1024)
        fileServerNum=1;
    chunkSize=fileinfo.file_size/fileServerNum;
    fileinfo.file_chunk_size=chunkSize;

    int fd=open(fileinfo.file_name,O_RDWR|O_CREAT,0666);
    ftruncate(fd,fileinfo.file_size);
    close(fd);
    recvCmd(socketFd,pcmd);

    //复制ip
    int i=0;
    char temp[25];
    for(i=0;i<fileServerNum;i++){
        Node_t *node=(Node_t *)malloc(sizeof(Node_t));
        node->next=NULL;
        memcpy(&node->fileinfo,&fileinfo,sizeof(msg_fileinfo_t));//复制文件信息
        if(i== fileServerNum-1)//最后一个文件块大小另外处理
            node->fileinfo.file_chunk_size=fileinfo.file_size-i*chunkSize;
        //printf("file_chunk_size %ld\n",node->fileinfo.file_chunk_size);
        node->fileinfo.offset = i*chunkSize;//文件位置偏移
        memcpy(temp,pcmd->buf+i*25,25);
        sscanf(pcmd->buf+i*25,"%s %d",node->ip,&node->port);
        quePush(&pf->que,node);
        pthread_cond_signal(&pf->cond);
    }
}
void cutDir(char *curDir)
{
    int len=strlen(curDir);
    int i=len-1;
    while(i>0 && curDir[i]!= '/') i--;
    if(i==0)
        curDir[1]=0;
    else
    {
        curDir[i]=0;
    }
}
void commandAnalyze(char *str,cmd_t *pcmd,char *curDir)
{
    //printf("commandAnalyze\n");
    int i=0,len = strlen(str);
    str[--len]=0;
    while(str[i]==' ') i++;
    if(!str[i]){
        pcmd->type=OTHER;
        return ;
    }
    if(i!= 0){
        memmove(str,str+i,strlen(str)-i);
    }
    const char *sep=" ";
    char *cmd,*path,*p;
    cmd = strtok(str, sep);
    path = strtok(NULL, sep);
    if(path){
        //printf("%s\n",path);
        p=strtok(NULL, sep);
        if(p)//格式错误，命令过多
        {
            pcmd->type=OTHER;
        }
        else {
            if(!strcmp(cmd,"cd"))
                pcmd->type=CD;
            else if(!strcmp(cmd,"gets"))
                pcmd->type=GETS;
            else if(!strcmp(cmd,"puts")){
                pcmd->type=PUTS;
            }
            else if(!strcmp(cmd,"mkdir"))
                pcmd->type=MKDIR;
            else if(!strcmp(cmd,"rmdir"))
                pcmd->type=RMDIR;
            else if(!strcmp(cmd,"rm"))
                pcmd->type=REMOVE;
            else{
                pcmd->type=OTHER;
                return;
            }
            if(pcmd->type==GETS)
            {/* 
                if(access(path,F_OK) != -1){
                    struct stat st;
                    lstat(path,&st);
                    if((st.st_mode & S_IFMT)==S_IFDIR){
                        pcmd->type=OTHER;
                        return;
                    }
                    pcmd->type=GETS2;
                    printf("gets file exist %s %ld\n",path,st.st_size);
                    sprintf(pcmd->buf,"%s %ld",path,st.st_size);
                    pcmd->len = strlen(pcmd->buf);
                    printf("%d %s\n",pcmd->type,pcmd->buf);
                    return;
                }*/
            }
            else if(pcmd->type==PUTS)//1发送文件信息
            {
                if(access(path,F_OK) != -1){
                    struct stat st;
                    lstat(path,&st);
                    if((st.st_mode & S_IFMT)==S_IFDIR){
                        pcmd->type=OTHER;
                        return;
                    }
                    msg_fileinfo_t fileinfo;
                    fileinfo.file_size=st.st_size;
                    strcpy(fileinfo.file_name,path);
                    fileinfo.offset=0;
                    fileinfo.file_chunk_size=0;
                    Compute_file_md5(path,fileinfo.file_md5sum);
                    pcmd->len=MSG_FILEINFO_HEAD_LEN+strlen(path)+1;
                    memcpy(pcmd->buf,&fileinfo,pcmd->len);
                    return;
                    //printf("gets file exist %s %ld\n",path,st.st_size);
                    //sprintf(pcmd->buf,"%s %ld",path,st.st_size);
                    //pcmd->len = strlen(pcmd->buf);
                    //printf("%d %s\n",pcmd->type,pcmd->buf);
                }
                else
                    pcmd->type=OTHER;
            }
            else if(pcmd->type==CD){
                if(strcmp(path,"..")==0){
                    if(strcmp(path,"/")==0){
                        pcmd->type=OTHER;
                        return;
                    }
                    else {
                        cutDir(curDir);
                    }
                }
                else if(strcmp(path,"/")==0)
                    curDir[1]=0;
                else if(strcmp(path,".")==0)
                    ;
                else{
                    int len=1;
                    int i=0;
                    while(path[i]){
                        if(path[i++]=='/'){
                            pcmd->type=OTHER;
                            return;
                        }
                    }
                    if(curDir[1]!=0){
                        len=strlen(curDir);
                        curDir[len++]='/';
                    }
                    strcpy(curDir+len,path);
                }
            }
            pcmd->len = strlen(path);
            strcpy(pcmd->buf,path);
            //printf("%s\n",pcmd->buf);
        }
    }
    else{
        if(!strcmp(cmd,"pwd")){
            pcmd->type=PWD;
        }
        else if(!strcmp(cmd,"exit") || !strcmp(cmd,"quit")){
            pcmd->type=EXIT;
        }
        else if(!strcmp(cmd,"ls")){
            pcmd->type=LS;
        }
        else{
            pcmd->type=OTHER;
        }
    }
}
