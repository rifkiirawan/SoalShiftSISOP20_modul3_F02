# SoalShiftSISOP20_modul3_F02

Praktikum Modul 3 Sisop 2020

Kelompok F02 (0099 &amp; 0142)

# Pembahasan Jawaban

## No 1 

### Source Code : [Triazone](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal1/soal2_traizone.c)

#### A. Triazone

Note: Triazone belum terselesaikan. Pokezone sudah.

### Source Code : [Pokezone](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal1/soal2_pokezone.c)

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

Halaman 0 Login
```
if(strcmp(input,"Login") == 0){
    printf("Username : ");
    scanf("%s",Username);
    printf("Password : ");
    scanf("%s",Password);
    sprintf(Data,"Username:%s|Password:%s",Username,Password);
    send(clientSocket,Data,500,0);
    recv(clientSocket,output,1024,0);
    child_id = fork();
    if (child_id < 0) {
         exit(EXIT_FAILURE);
    }
    if (child_id == 0) {
         char *argv[] = {"clear", NULL}; 
         execv("/usr/bin/clear", argv);                
    } else {
         while ((wait(&status)) > 0);
    }
    if(strcmp(output,"success")==0){
         halaman=1;
         printf("login success\n");
    }
    else {
         halaman=0;
         printf("login failed");
    }
    continue;
}
```
Didalam login pada client, client diminta untuk memasukkan username dan password, kemudian dikirimkan ke server. 

#### B. TapServer

## No 3

### Source Code : [3](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal3/soal3.c)

## No 4

### Source Code : [4a](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal4/soal4a.c)
### Source Code : [4b](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal4/soal4b.c)
### Source Code : [4c](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal4/soal4c.c)

#### 4a. Berisi sebuah program c untuk membuat perkalian 2 array dengan ukuran 4x2 dan 2x5, yang berisikan angka 1-20 yang akan ditampilkan di layar.

Mendeklarasikan array dan isi matriks dengan menggunakan array 2 dimensi.
```
int first[4][2] = {{1,2},
                   {3,4},
		   {5,6},
		   {7,8}};
  int second[2][5] = {{1,1,1,2,3},
		      {4,1,6,1,8}};
```

Melakukan perkalian antara 2 matriks dan menyimpan variabel yang akan di passing untuk soal 4b.
```
for (c = 0; c < 4; c++) {
		for (d = 0; d < 5; d++) {
			for (k = 0; k < 2; k++) {
				sum = sum + first[c][k] * second[k][d];
			}
			multiply[c][d] = sum;
			sum = 0;
		}
	}
 
	for (c = 0; c < 4; c++) {
		for (d = 0; d < 5; d++) {
			value[5*c+d] = multiply[c][d];
			printf("%4d",multiply[c][d]);
		}
		printf("\n");
	}
```

#### 4b. Membuat program untuk mengambil data hasil perkalian matriks pada soal 4a dan dilakukan pencarian faktorial dari masing-masing angka pada matriks, yang juga akan ditampilkan.


1. Menampilkan hasil dari perkalian matriks pada soal 4a. 
```
for (int i = 0;i < 20;i++)
	{
		d[i].angka = value[i];
		if (i % 5 == 0) printf("\n");
		printf("%4d", value[i]);
		pthread_create(&tid[i],NULL, &jumn, (void*)&d[i]);
	}
	printf("\n");
```

2. Melakukan pencarian faktorial dari tiap-tiap angka pada matriks.
        Setelah menampilkan perkalian matriks pada kedua matriks, akan dilakukan thread, yang memanggil fungsi jumn yang mengembalikan nilai faktorial dari tiap angka pada array, dan hasilnya akan ditampilkan.
```
int jumlah(int n) 
{ 
	int sum=0;
	for(n;n>0;n--)
	{
		sum+=n;
	}
	return sum;
}

void *jumn(void* arg)
{
	data* d = (data*) arg;
        d->hasil=jumlah(d->angka);
}
.
.
.
for(int i=0; i< 20; i++)
	{
		if (i % 5 == 0) printf("\n");
		printf("%d\t", d[i].hasil);
		pthread_join(tid[i],NULL);
	}
```

#### 3. Mencari jumlah file yang ada pada direktori saat ini. 
```
if (fork() == 0) 
  {
    dup2(pipe1[1], 1);
    // close fds
    close(pipe1[0]);
    close(pipe1[1]);
    char *argv1[] = {"ls", NULL};
		execv("/bin/ls", argv1);
  }
  else
  {
    dup2(pipe1[0], 0);
    close(pipe1[0]);
    close(pipe1[1]);
    char *argv1[] = {"wc", "-l", NULL};
		execv("/usr/bin/wc", argv1);
  }
  ```
