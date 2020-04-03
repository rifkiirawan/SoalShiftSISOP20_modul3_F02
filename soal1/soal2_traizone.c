#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
void main(){
    key_t key = 1234;
    int *value;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);
    *value = 10;
    int mode=0,menu=0,menuCap=0;
    while(1){
        printf("Selamat datang di Traizone\nSilahkan pilih Mode:\n1. Normal Mode\n2. Capture Mode\nMasukkan Angka: ");
        scanf("%d",&mode);
        if(mode==1){ //NormalMode
            printf("Silahkan pilih Menu:\n1. Cari Pokemon\n2. Pokedex\n3. Shop\nMasukkan Angka: ");
            scanf("%d",&menu);
            if(menu==1){//cariPokemon

            }
            else if(menu==2){//Pokedex

            }
            else{//Shop

            }
        }
        else{//CaptureMode
            printf("Silahkan pilih Menu:\n1. Tangkap\n2. Item\n3. Keluar\nMasukkan Angka: ");
            scanf("%d",&menuCap);
            if(menuCap==1){//Tangkap

            }
            else if(menu==2){//Item

            }
            else{//Keluar
                mode=1;
                continue;
            }
        }
    }
    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);
}
