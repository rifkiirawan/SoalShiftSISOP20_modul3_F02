# SoalShiftSISOP20_modul3_F02

Praktikum Modul 3 Sisop 2020

Kelompok F02 (0099 &amp; 0142)

# Pembahasan Jawaban

## No 1 

### Source Code : [Triazone](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal1/soal2_traizone.c)
### Source Code : [Pokezone](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal1/soal2_pokezone.c)

Note: Triazone belum terselesaikan. Pokezone sudah.

#### A. Triazone

#### B. Pokezone

Pokezone menggunakan thread sebanyak 3 thread dan shared memory sebanyak 10 variable.

```
if(pthread_equal(id,tid[0])){ //thread shutdown
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
``` 
Thread Pertama

Digunakan untuk pilihan shutdown. Menggunakan fork-exec untuk kill process sesuai kedua PID program.

```
else if(pthread_equal(id,tid[1])){ //thread tambah item jualan
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
```

Thread Kedua

Digunakan untuk menambah item jualan setiap 10 detik sekali (sleep 10) dan apabila sudah mencapai maksimal 200, item tidak akan bertambah.

```
else if(pthread_equal(id,tid[2])){ //thread random pokemonnya
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
```

Thread Ketiga

Digunakan untuk random pokemon. Pertama, random type terlebih dahulu, terdapat 3 type yang masing-masing kemungkinannya berbeda. Dirandom dari 0-100, jika angka 0-79 maka normal, jika 80-94 maka rare, jika 95-100 maka legendary. Kemudian diisi sesuai list yang ada pada soal. Random kedua yaitu random apakah dia shiny atau tidak, dengan kemungkinan 1/8000. Maka setiap random angka, keluar angka 1, dia merupakan shiny. Setelah itu dicatat pada shared memory, agar triazone dapat mengakses hasil dari pokezone.


## No 2

### Source Code : [TapClient](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal2/tapclient.c)
### Source Code : [TapServer](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal2/tapserver.c)

Kedua Jawaban menggunakan socked Client dan Server.

#### A. TapClient

Terdapat 2 halaman masing-masing 2 pilihan. Halaman pertama berisi login atau register. Halaman Kedua berisi Find dan logout.

#### B. TapServer

## No 3

### Source Code : [3](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal3/soal3.c)

## No 4

### Source Code : [4a](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal4/soal4a.c)
### Source Code : [4b](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal4/soal4b.c)
### Source Code : [4c](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal4/soal4c.c)

