#ifndef __COMMAND_H__
#define __COMMAND_H__
#include "common.h"

int SignCmd(int newFd,char *username,user_token_t *userToken,cmd_t *pcmd);
int cdCmd(int clientsfd,unsigned int uid,unsigned int *curDirId,cmd_t *pcmd);
void lsCmd(int clientsfd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd);
int mkdirCmd(int newFd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd);
int removeCmd(int newFd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd);
int rmdirCmd(int newFd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd);
int putsCmd(int clientsfd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd);
int getsCmd(int newFd,unsigned int uid,unsigned int curDirId,cmd_t *pcmd);
void getSalt(char *salt,int len);
void autoUpdateToken(user_token_t *userToken);
#endif
