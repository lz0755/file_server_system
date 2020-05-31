#ifndef __COMMAND_H__
#define __COMMAND_H__
#include "common.h"

int putsCmd(int newFd,unsigned int uid,cmd_t *cmd);
int getsCmd(int newFd,unsigned int uid);
int tokenCmd(int newFd,user_token_t *userToken,cmd_t *cmd);
#endif
