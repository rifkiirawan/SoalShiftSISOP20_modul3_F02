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

int *shutdown,*stockLul,*stockBall,*stockBerry,*PokeShiny,*PokeName,*PokeEscape,*PokeCapture,*PokeDollar,*RandomPokemon,*traiPID;
int PokeSlot[7],PokeAP[7],PokeNames[7],PokeDollars[7],PokeisShiny[7],PokeCount,CaptureMode,CariPokemon,Pokedex,Shop,LulEfek;
int FoundPokemon, LullabyPowder, PokeBall, Berry, Dollar;
pthread_t tid[5];

int Randomize(int chance);
void printPokeName(int i);
void Inventory();
void PrintShop();
void PrintInput();

void* triazone(void *arg){
    pthread_t id=pthread_self();
    if(pthread_equal(id,tid[0])){ //cariPokemon
        while(1){
            while(FoundPokemon==1);
            while(CariPokemon==0);
            sleep(10);
            if(CariPokemon==0) continue;
            int cek = Randomize(60);
            if(cek==1){
                *RandomPokemon=1;
                FoundPokemon=1;
                printf("Found a Pokemon. Go to Capture Mode?\n");
            }
            else printf(" Not found any Pokemon.\n");
        }
    }
    else if(pthread_equal(id,tid[1])){ //AP manager POKEDEX
        while(1){
            while(CaptureMode==1);
            sleep(10);
            if(CaptureMode==1) continue;
            int a;
            for(a=0;a<7;a++){
                if(PokeSlot[a]==0) continue;
                else{
                    PokeAP[a]-=10;
                    if(PokeAP[a]<10){
                        int cek = Randomize(90);
                        if(cek==1) PokeSlot[a]=0;
                        else PokeAP[a]=50;
                    }
                }
            }
        }
    }
    else if(pthread_equal(id,tid[2])){//lullaby powder efek manager
        while(1){
            while(LulEfek==0);
            sleep(10);
            LulEfek=0;
        }
    }
    else if(pthread_equal(id,tid[3])){
        while(1){
            while(CaptureMode==0);
            sleep(20);
            if(CaptureMode==0) continue;
            if(LulEfek==0){
                int ER= *PokeEscape;
                int cek=Randomize(ER);
                if(cek==1){
                    CaptureMode=0;
                    CariPokemon=0;
                    Pokedex=1;
                    Shop=0;
                    printf("Pokemon Run. Back to Pokedex\n");
                }
                else printf("Pokemon look at you\n");
            }
        }
    }
    else if(pthread_equal(id,tid[4])){
        while(1){
            if(Pokedex==1) Inventory();
            if(Shop==1) PrintShop();
            if(CaptureMode==1){
                printf("Pokemon ");
                printPokeName(*PokeName);
                if(*PokeShiny) printf(" is Shiny\n");
                else printf("\n");
            }

            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            if(a==9 && b==9 && c==9 && FoundPokemon==1){
                CaptureMode=1; CariPokemon=0; Pokedex=0;
                Shop=0; FoundPokemon=0;
                printf("Capture Mode\n");
                continue;
            }
            if(CaptureMode==0 && a==1){
                if(b==1){
                    CariPokemon=1; Pokedex=0; Shop=0;
                    printf("Find Pokemon\n");
                    continue;
                }
                else if(b==2){
                    CariPokemon=0; Pokedex=1; Shop=0;
                    printf("Pokedex\n");
                    continue;
                }
                else if(b==3){
                    CariPokemon=0; Pokedex=0; Shop=1;
                    printf("Shop\n");
                    continue;
                }
            }
            if(Pokedex==1){
                if(a==2 && b==1 && c==0){ //use Berry
                    if(Berry<1) printf("No Berry\n");
                    else if(PokeCount==0) printf("No Pokemon\n");
                    else{
                        Berry-=1;
                        int i;
                        for(i=0;i<7;i++){
                            if(PokeSlot[i]==1) PokeAP[i]+=10;
                        }
                        printf("Used Berry\n");
                    }
                }
                if(a==2 && b==2 && c<7){
                    if(PokeSlot[c]==1){
                        printPokeName(PokeNames[c]);
                        printf(" released\n");
                        Dollar+=PokeDollars[c];
                        PokeSlot[c]=0;
                        PokeCount-=1;
                    }
                    else printf("Empty Slot\n");
                }
                else if(c>6) printf("Out of Range\n");
            }
            if(Shop==1){
                if(a==3 && b==1){ //buy lulPowder
                    if((LullabyPowder+c)>99) c=99-LullabyPowder;
                    if(c> *stockLul) c=*stockLul;
                    if(c<1) printf("Item out of limit/stock, Can't buy\n");
                    else if(Dollar<(60*c)) printf("Not Enough Money\n");
                    else{
                        Dollar-=(60*c);
                        LullabyPowder+=c;
                        *stockLul=*stockLul-c;
                        printf("Lullaby Powder added success\n");
                    }
                }
                if(a==3 && b==2){
                    if((PokeBall+c)>99) c=99-PokeBall;
                    if(c> *stockBall) c=*stockBall;
                    if(c<1) printf("Item out of limit/stock, Can't buy\n");
                    else if(Dollar<(5*c)) printf("Not Enough Money\n");
                    else{
                        Dollar-=(5*c);
                        PokeBall+=c;
                        *stockBall=*stockBall-c;
                        printf("Pokeball added success\n");
                    }
                }
                if(a==3 && b==3){
                    if((Berry+c)>99) c=99-Berry;
                    if(c> *stockBerry) c=*stockBerry;
                    if(c<1) printf("Item out of limit/stock, Can't buy\n");
                    else if(Dollar<(5*c)) printf("Not Enough Money\n");
                    else{
                        Dollar-=(15*c);
                        Berry+=c;
                        *stockBerry=*stockBerry-c;
                        printf("Berry added success\n");
                    }
                }
            }
            if(CaptureMode==1){
                if(a=4 && b==1){
                    if(PokeBall<1) printf("Pokeball empty\n");
                    else{
                        PokeBall-=1;
                        printf("Shoot Pokeball\n");
                        int cek;
                        int capturerate=*PokeCapture;
                        if(LulEfek==1) cek = Randomize(capturerate+20);
                        else cek=Randomize(capturerate);

                        if(cek==1){
                            printf("Pokemon Caught\n");
                            if(PokeCount>6){
                                Dollar+=*PokeDollar;
                                printf("No space, Pokemon Released\n");
                            }
                            else {
                                int i;
                                for(i=0;i<7;i++){
                                    if(PokeSlot[i]==0){
                                        PokeNames[i]=*PokeName;
                                        PokeAP[i]=100;
                                        PokeDollars[i]=*PokeDollar;
                                        PokeisShiny[i]=*PokeShiny;
                                        PokeCount++;
                                        PokeSlot[i]=1;
                                        break;
                                    }
                                }
                            }
                            CaptureMode=0;
                            CariPokemon=0;
                            Pokedex=1; Shop=0; LulEfek=0;
                        }
                        else printf("Pokemon can't catch\n");
                        }
                    if(a==4 && b==2){
                        if(LullabyPowder<1) printf("Not enough LulPowder\n");
                        else{
                            LullabyPowder-=1;
                            LulEfek=1;
                            printf("Lullaby Powder used\n");
                        }
                    }
                    if(a==4 && b==3){
                        CaptureMode=0; CariPokemon=0; Pokedex=1;Shop=0; LulEfek=0;
                        printf("Run from encounter\n");
                    }
                }
            }
        }
    }
}

void main(){
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
    key = 1334; int shmid10 = shmget(key, sizeof(int), IPC_CREAT | 0666); traiPID = shmat(shmid10, NULL, 0);
    
    int i=0,err;
    *traiPID=getpid(); *shutdown=1; *RandomPokemon=0;

    int j;
    for(j=0;j<7;j++){
        PokeSlot[j]=0;
        PokeAP[j]=0;
        PokeNames[j]=0;
        PokeDollars[j]=0;
        PokeisShiny[j]=0;
    }
    PokeCount=0; CaptureMode=0; CariPokemon=0; Pokedex=0; Shop=0; LulEfek=0; FoundPokemon=0;
    LullabyPowder=0; Berry=0; PokeBall=10; Dollar=500;

    printf("%d\n",*traiPID);
    PrintInput();
    while(i<5){ // loop sejumlah thread
        err=pthread_create(&(tid[i]),NULL,&triazone,NULL); //membuat thread
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
    pthread_join(tid[3],NULL);
    pthread_join(tid[4],NULL);
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
    shmdt(traiPID); shmctl(shmid10, IPC_RMID, NULL);
}

int Randomize(int chance){
    srand(time(NULL));
    int temp = rand()%100;
    if(temp<chance) return 1;
    else return 0;
}

void printPokeName(int i){
    if(i==1) printf("Bulbasaur");
    else if(i==2) printf("Charmander");
    else if(i==3) printf("Squirtle");
    else if(i==4) printf("Rattata");
    else if(i==5) printf("Caterpie");
    else if(i==6) printf("Pikachu");
    else if(i==7) printf("Eevee");
    else if(i==8) printf("Jigglypuff");
    else if(i==9) printf("Snorlax");
    else if(i==10) printf("Dragonite");
    else if(i==11) printf("Mew");
    else if(i==12) printf("Mewtwo");
    else if(i==13) printf("Moltres");
    else if(i==14) printf("Zapdos");
    else if(i==15) printf("Articuno");
}

void Inventory(){
    int i;
    for(i=0;i<7;i++){
        if(PokeSlot[i]==1){
            printPokeName(PokeNames[i]);
            printf("\t AP = %d",PokeAP[i]);
            if(PokeisShiny[i]==1) printf("\t is shiny\n");
            else printf("\n");
        }
        else printf("Empty slot\n");
    }
    printf("PokeBall = %d\n",PokeBall);
    printf("Lullaby Powder = %d\n",LullabyPowder);
    printf("Berry = %d\n",Berry);
    printf("PokeDollar = %d\n",Dollar);
}

void PrintShop(){
    printf("Welcome to Shop\nList item to buy:\n");
    printf("Lullaby Powder\tPrice 60 PokeDollar\n");
    printf("Pokeball\tPrice 5 PokeDollar\n");
    printf("Berry\tPrice 15 PokeDollar\n");
    printf("Your Inventory: (Maks 99 item)\n");
    printf("PokeBall = %d\n",PokeBall);
    printf("Lullaby Powder = %d\n",LullabyPowder);
    printf("Berry = %d\n",Berry);
    printf("PokeDollar = %d\n",Dollar);
}

void PrintInput(){
    printf("Input Guide:\na b c\n");
    printf("1 1 0\tFind Pokemon.\n");
    printf("1 2 0\tPokedex.\n");
    printf("1 3 0\tShop.\n");
    printf("2 1 0\tUse Berry. From Pokedex.\n");
    printf("2 2 i\tLet Pokemon (i 0-6) go. From Pokedex.\n");
    printf("3 1 i\tBuy i Lullaby Powder. From Shop.\n");
    printf("3 2 i\tBuy i Pokeball. From Shop.\n");
    printf("3 3 i\tBuy i Berry. From Shop.\n");
    printf("9 9 9\tGo to Capture Mode if Pokemon found.\n");
    printf("4 1 0\tCatch Pokemon, use Pokeball.\n");
    printf("4 2 0\tUse Lullaby Powder.\n");
    printf("4 3 0\tRun. Get out from Pokedex.\n");
}