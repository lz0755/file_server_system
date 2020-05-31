#ifndef __CLIENT__
#define __CLIENT__
#include "factory.h"

void commandAnalyze(char *str,cmd_t *pcmd,char *curDir);
int recvCycle(int sfd,void* pStart,int recvLen);
int serverData(int socketFd,Factory_t *pf,cmd_t *pcmd,char *curDir,msg_fileinfo_t *pfileInfo);
void cutDir(char *curDir);
void putsCmd(int socketFd,Factory_t *pf,cmd_t *pcmd,msg_fileinfo_t *pfileInfo);
void getsCmd(int socketFd,Factory_t *pf,cmd_t *pcmd);
void usage();
#endif
