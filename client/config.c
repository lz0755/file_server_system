#include <stdio.h>
#include <string.h>
#include "config.h"
static struct config config[10];
static int configsize=0;
int initConfig()
{
    FILE *fp;
    fp = fopen("../conf/server.conf","ab+");
    if(fp==NULL) {
        perror("fopen");
        return -1;
    }
    char buf[81];
    memset(config,0,sizeof(config));
    int j,k;
    while(configsize < 10 && fgets(buf,sizeof(buf),fp) != NULL){
        //printf("%s\n",buf);
        if(strlen(buf)>=sizeof(buf)-1)
            return -1;
        j=0;
        k=0;
        while(j<30 && buf[j] && buf[j] != '=') config[configsize].key[k++]=buf[j++];
        if(j==30 || buf[j] == 0){
            return -1;
        }
        k=0;
        j++;
        while(buf[j]) config[configsize].value[k++]=buf[j++];
        configsize++;
    }
    fclose(fp);
    return 0;
}
char *getConfig(const char *key)
{
    int i=0;
    for(;i<configsize;i++){
        if(strcmp(key,config[i].key)==0)
            return config[i].value;
    }
    return NULL;
}