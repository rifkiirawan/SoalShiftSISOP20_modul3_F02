#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

typedef struct tdata {
    char d[200];
    char name[200];
}tdata;

void lowcase(char* c){
    for (int i = 0; i < strlen(c); i++){
        c[i] = tolower(c[i]);
    }
}

void* move(void* arg) {
    tdata* d = (tdata*)arg;
    char pathold[400], pathnew[400];
    sprintf(pathold, "%s/%s",d->d,d->name);
    char* ext = strrchr(d->name,'.');
    if(ext != NULL){
        char ori[150];
        strcpy(ori,ext+1);
        lowcase(ori);
        mkdir(ori,0755);
        sprintf(pathnew,"./%s/%s", ori, d->name);
    }else{
        mkdir("Unknown",0755);
        sprintf(pathnew,"./Unknown/%s",d->name);
    }
    rename(pathold,pathnew);
    free(d);
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
        }else {
            mkdir("Unknown", 0755);
            sprintf(pathnew, "./Unknown/%s", name);
        }
        rename(argmod[i], pathnew);
    }
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argmod[]){
    DIR* d;
    char namadir[200];
    
    if(argc == 2 && !strcmp(argmod[1], "*")){
        if((d = opendir(".")) == NULL){
            printf("Folder tidak dapat dibuka.\n");
            exit(EXIT_FAILURE);
        }
        strcpy(namadir, ".");
    }else if(argc == 3 && !strcmp(argmod[1], "-d")){
        if((d = opendir(argmod[2])) == NULL){
            printf("Folder tidak dapat dibuka.\n");
            exit(EXIT_FAILURE);
        }
        strcpy(namadir, argmod[2]);
    }else if(argc >2 && !strcmp(argmod[1], "-f")){
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
    }else{
        printf("Argumen salah.\n");
        exit(EXIT_FAILURE);
    }

    int n=0;
    struct dirent* ent;
    while((ent = readdir(d)) != NULL){
        if(ent->d_type == DT_REG) n++;
    }

    pthread_t threads[n];
    int index=0;
    rewinddir(d);
    while((ent = readdir(d)) != NULL){
        if(ent -> d_type != DT_REG) continue;
        if (!strcmp(ent->d_name, argmod[0]+2)){
            threads[index] = 0;
            index++;
            continue;
        }
        tdata* data = malloc(sizeof(tdata));
        strcpy(data->d, namadir);
        strcpy(data->name, ent->d_name);
        pthread_create(&threads[index], NULL, move, (void*)data);
        index++;
    }
    for(int i=0; i<n ; i++){
        if(threads[i]) pthread_join(threads[i],NULL);
    }
    exit(EXIT_SUCCESS);
}
