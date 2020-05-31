#ifndef __CONFIG__
#define __CONFIG__
struct config{
    char key[30];
    char value[50];
};
int initConfig();
char *getConfig(const char *key);
#endif