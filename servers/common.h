#ifndef __COMMON__
#define __COMMON__

#define DEBUG_SERVER

enum command {
    CD=1,
    LS,
    MKDIR,
    RMDIR,
    PUTS,
    GETS,
    GETS2,
    REMOVE,
    PWD,
    EXIT,
    LOGIN,
    LOGINSUCC,
    LOGINFAIL,
    SIGNUP,
    SIGNUPSUCC,
    SIGNUPFAIL,
    TOKEN,
    OTHER
};
#define SIZE_100MB 100*1024*1024
#define CMD_HEAD_LEN 8
typedef struct{
    int len;
    int type;
    char buf[1000];
}cmd_t;
#define MSG_FILEINFO_HEAD_LEN 64
typedef struct{
    long offset;
    long file_size;
    long file_chunk_size;
    char file_md5sum[40];
    char file_name[256];//256-24
}msg_fileinfo_t;

typedef struct user_token{
    unsigned int uid;
    char token[40];
}user_token_t;

struct uint_t{
    unsigned int uint32;
};
void sendAckCmd(int fd,cmd_t *pcmd,int type);
int sendCmd(int fd,cmd_t *pcmd,int type,int len);
int recvCmd(int socketFd,cmd_t *pcmd);
int sendFile(int socketFd);
int recvFile(int socketFd,msg_fileinfo_t *pfileInfo);
#endif
