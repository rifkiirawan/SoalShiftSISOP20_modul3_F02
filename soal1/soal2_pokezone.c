#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include <time.h>
#include <stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
pthread_t tid[3]; //inisialisasi array untuk menampung thread dalam kasus ini ada 3 thread
pid_t child_id;
int status;
int pokezonePID,namaPokemon,escape,capture,pokedollar,shiny,*RandomPokemon;
int *shutdown,*stockLul,*stockBall,*stockBerry,*PokeShiny,*PokeName,*PokeEscape,*PokeCapture,*PokeDollar;
void* pokezone(void *arg){
    pthread_t id=pthread_self();
    if(pthread_equal(id,tid[0])){
        printf("Selamat datang di Pokezone\nSilahkan pilih Fitur:\n1. Shutdown Game\nMasukkan Angka: ");
        scanf("%d",&*shutdown);
        child_id = fork();
        if (child_id < 0) {
            exit(EXIT_FAILURE);
        }
        if (child_id == 0) {
            char arr[100];
            sprintf(arr,"%d",pokezonePID);
            char *argv[] = {"kill",arr, NULL}; 
            execv("/bin/kill", argv);       
        } else {
            while ((wait(&status)) > 0);
        }   
    }
    else if(pthread_equal(id,tid[1])){
        while(1){
            sleep(10);
            if(*stockLul<=190){
                *stockLul+=10;
            } else *stockLul=200;
            if(*stockBall<=190){
                *stockBall+=10;
            } else *stockBall=200;
            if(*stockBerry<=190){
                *stockBerry+=10;
            } else *stockBerry=200;
            printf("Lul: %d Ball: %d Berry: %d\n",*stockLul,*stockBall,*stockBerry);
        }
    }
    else if(pthread_equal(id,tid[2])){
        while(1){
            sleep(1);
            srand(time(NULL));   // Initialization, should only be called once.
            int randomType = rand()%100;
            int randomNama = rand()%5;
            if(randomType<80){
                 escape=5; capture=70; pokedollar=80; namaPokemon=randomType;
            }
            else if(randomType<95){
                 escape=10; capture=50; pokedollar=100; namaPokemon=randomType+5;
            }
            else{
                 escape=20; capture=30; pokedollar=200; namaPokemon=randomType+10;
            }
            int randomShiny=rand()%8000;
            if(randomShiny==1){
                escape+=5; capture-=20; pokedollar+=5000; shiny=1;
            } else shiny=0;
            printf("Escape %d Capture %d Pokedollar %d Nama %d Shiny %d\n",escape,capture,pokedollar,namaPokemon,shiny);
            if(*RandomPokemon==1){
                *PokeEscape=escape; *PokeCapture=capture; *PokeDollar=pokedollar; *PokeName=namaPokemon; *PokeShiny=shiny; *RandomPokemon=0;
            }
        }
    }
    return NULL;
}

void main(){
    pokezonePID=getpid();
    key_t key = 1234; int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666); shutdown = shmat(shmid, NULL, 0);
    key = 1244; int shmid1 = shmget(key, sizeof(int), IPC_CREAT | 0666); stockLul = shmat(shmid1, NULL, 0);
    key = 1254; int shmid2 = shmget(key, sizeof(int), IPC_CREAT | 0666); stockBall = shmat(shmid2, NULL, 0);
    key = 1264; int shmid3 = shmget(key, sizeof(int), IPC_CREAT | 0666); stockBerry = shmat(shmid3, NULL, 0);
    key = 1274; int shmid4 = shmget(key, sizeof(int), IPC_CREAT | 0666); PokeShiny = shmat(shmid4, NULL, 0);
    key = 1284; int shmid5 = shmget(key, sizeof(int), IPC_CREAT | 0666); PokeCapture = shmat(shmid5, NULL, 0);
    key = 1294; int shmid6 = shmget(key, sizeof(int), IPC_CREAT | 0666); PokeDollar = shmat(shmid6, NULL, 0);
    key = 1304; int shmid7 = shmget(key, sizeof(int), IPC_CREAT | 0666); PokeEscape = shmat(shmid7, NULL, 0);
    key = 1314; int shmid8 = shmget(key, sizeof(int), IPC_CREAT | 0666); PokeName = shmat(shmid8, NULL, 0);
    key = 1324; int shmid9 = shmget(key, sizeof(int), IPC_CREAT | 0666); RandomPokemon = shmat(shmid9, NULL, 0);
    *shutdown=0; *stockLul=100; *stockBall=100; *stockBerry=100; *RandomPokemon=1;

    pid_t child_id;
    int i=0;
    int err;
    while(i<3){ // loop sejumlah thread
        err=pthread_create(&(tid[i]),NULL,&pokezone,NULL); //membuat thread
        if(err!=0){ //cek error
            printf("\n can't create thread : [%s]",strerror(err));
        }
        else{
            printf("\n create thread success\n");
        }
        i++;
    }
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    exit(0);
    shmdt(shutdown); shmctl(shmid, IPC_RMID, NULL);
    shmdt(stockLul); shmctl(shmid1, IPC_RMID, NULL);
    shmdt(stockBall); shmctl(shmid2, IPC_RMID, NULL);
    shmdt(stockBerry); shmctl(shmid3, IPC_RMID, NULL);
    shmdt(PokeShiny); shmctl(shmid4, IPC_RMID, NULL);
    shmdt(PokeCapture); shmctl(shmid5, IPC_RMID, NULL);
    shmdt(PokeDollar); shmctl(shmid6, IPC_RMID, NULL);
    shmdt(PokeEscape); shmctl(shmid7, IPC_RMID, NULL);
    shmdt(PokeName); shmctl(shmid8, IPC_RMID, NULL);
    shmdt(RandomPokemon); shmctl(shmid9, IPC_RMID, NULL);
}
