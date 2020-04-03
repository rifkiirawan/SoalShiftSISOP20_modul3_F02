#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<ctype.h>

void lowcase(char* c){
    for (int i = 0; i < strlen(c); i++){
        c[i] = tolower(c[i]);
    }
}

void makefile(int argc , char* argmod[],char* name, char* ext){
    for(int i=2; i<argc; i++){
        char pathnew[500];
        if(ext != NULL){
            char pathold[200];
            strcpy(pathold,ext+1);
            lowcase(pathold);
            mkdir(pathold,0755);
            sprintf(pathnew, "./%s/%s", pathold,name);
        } else {
            mkdir("Unknown", 0755);
            sprintf(pathnew, "./Unknown/%s", name);
        }
        rename(argmod[i], pathnew);
    }
    exit(EXIT_SUCCESS);
}


int main(int argc, char* argmod[]){
    if(argc >2 && strcmp(argmod[1], "-f") == 0){
        const char str[100];
        for(int i=2; i<argc;i++){
        char* name = strrchr(argmod[i],'/');
        if (name==NULL) name = argmod[i];
        else name++;
        char* ext;
        ext = strrchr(argmod[i],'.');
        printf("%s\n",ext+1);
        makefile(argc,argmod,name,ext);
        }
        
    }
    // if(strcmp(argmod[1]), "*"){

    // }
    // if(strcmp(argmod[1]), "-d"){

    // }
    
    return 0;
}
