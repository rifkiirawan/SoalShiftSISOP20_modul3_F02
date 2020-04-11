# SoalShiftSISOP20_modul3_F02

Praktikum Modul 3 Sisop 2020

Kelompok F02 (0099 &amp; 0142)

# Pembahasan Jawaban

## No 1 

### Source Code : [Triazone](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal1/soal2_traizone.c)

#### A. Triazone

Terdapat 5 thread yaitu:

##### 1. Thread Mencari Pokemon
```
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
```
Melakukan pengecekan setiap 10 detik dan apabila pemain sedang mencari, maka akan diberitahu apabila menemukan pokemon.

##### 2. Thread Manager AP
```
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
```
Setiap 10 detik, setiap pokemon akan berkurang AP nya sebanyak 10 detik. Kemudian akan hilang apabila AP=0;

##### 3. Thread Lullaby Powder
```
else if(pthread_equal(id,tid[2])){//lullaby powder efek manager
        while(1){
            while(LulEfek==0);
            sleep(10);
            LulEfek=0;
        }
}
```
Apabila Lullaby Powder digunakan, maka selama 10 detik efeknya akan hilang.

##### 4. Thread Penangkapan Pokemon
```
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
```    
Apabila pokemon didapatkan dari pencarian pokemon, maka akan diberitahukan apakah pokemon tersebut dapat ditangkap atau lari.

##### 5. Thread Main

Thread ini sangat panjang sehingga untuk codingan dapat dibuka di link atas. Isinya untuk menjalankan seluruh bagian game, mulai dari input yang terdapat 3 angka inputan. Angka pertama untuk peletakan dia berada di Pokedex, Normal mode, shop atau Capture mode. Angka kedua untuk menginformasikan kegiatan apa yang dilakukan di lokasi tersebut, misal shop terdapat berry, pokeball, dan lullaby powder. Untuk angka yang ketiga, menginformasikan jumlah pembelian pada shop. Segala informasi yang berkaitan dengan permainan, telah disampaikan kepada pemain pada saat bermain.


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
            char arr[100];
            sprintf(arr,"%d",*traiPID);
            char *argv[] = {"kill",arr, NULL}; 
            execv("/bin/kill", argv);
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

Kedua Jawaban menggunakan socked Client dan Server.

### Source Code : [TapClient](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal2/tapclient.c)

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
Didalam login pada client, client diminta untuk memasukkan username dan password, kemudian dikirimkan ke server untuk dicocokkan pada data yang sudah ada di akun.txt.

Register
```
 if(strcmp(input,"Register") == 0){
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
                // system("clear");
                if(strcmp(output,"success")==0){
                    halaman=0;
                    printf("register success\n");
                }
                else {
                    halaman=0;
                    printf("register failed");
                }
                continue;
}
```
Pada Register, dengan tampilan yang sama dengan login, akan tetapi apapun yang dimasukkan sebagai username dan password tidak akan dicocokkan dengan data yang ada, tetapi langsung dimasukkan pendaftaran baru pada data sehingga dapat terjadi data ganda. Apabila sudah selesai register, akan kembali pada halaman login untuk login terlebih dahulu sebelum bermain.

Halaman 1 untuk bermain dan logout
```
if(strcmp(input,"Logout")==0){
                halaman=0;
                continue;
}
```
Apabila logout, halaman akan langsung reset ke halaman 0, dan harus kembali masuk melalui login apabila ingin bermain.

Find Match
```
if(strcmp(input,"Find")==0){
	send(clientSocket,input,500,0);
	printf("Waiting for opponent.....\n");
	int read=recv(clientSocket,output,1024,0);
	output[read]='\0';
	pthread_t thread;
	    pthread_create(&thread, NULL, listening, output)
	    printf("Game dimulai silahkan tap ​tap​ secepat mungkin!!\n");
	child_id = fork();
	if (child_id < 0) {
	    exit(EXIT_FAILURE);
	}
	if (child_id == 0) {
	    char *argv[] = {"stty", "raw", NULL}; 
	    execv("/bin/stty", argv);                
	} else {
	    while ((wait(&status)) > 0);
	}
	while(1){
	    input[0]=getchar();
	    input[1]='\0';
	    send(clientSocket,input,500,0);
	    int read=recv(clientSocket,output,1024,0);
	    output[read]='\0';
	    if(!strstr(output,"hit!!")){
		child_id = fork();
		if (child_id < 0) {
		    exit(EXIT_FAILURE);
		}
		if (child_id == 0) {
		    char *argv[] = {"stty", "cooked", NULL}; 
		    execv("/bin/stty", argv);                
		} else {
		    while ((wait(&status)) > 0);
		}
		printf("%s\n",output);
		break;
	    }
	     printf("%s\n",output);
	}
}
```
Dalam find, apabila sudah ditemukan pemain, maka langsung dimulai dengan tap tap spasi, menggunakan stty raw dan stty cooked untuk mengambil char spasi tanpa enter. Kemudian spasi dikirimkan pada server, server akan membalas apabila pemain terkena hit. Terdapat thread agar apabila pemain tidak menekan apapun, pemain masih dapat terkena hit dan pengurangan poin akan muncul pada terminal.

```
void* listening(char cnt[]){
    int clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    char data[1024];
    char output[1024];

    connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
    sprintf(data,"%sListen",cnt);
    send(clientSocket,data,1024,0);
    while(1){
        int read = recv(clientSocket,output,1024,0);
        printf("%s\n",output);
		data[read] = '\0';
    }
}
```
Isi dari thread ini hanya untuk selalu menunggu kiriman sinyal dari server apabila terkena hit dan pengurangan nilai, langsung muncul di terminal.

### Source Code : [TapServer](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal2/tapserver.c)

#### B. TapServer


Login

```
if(strcmp(data,"Login") == 0){
    FILE *file = fopen("akun.txt","r");
    if(!file){
	FILE *file2 = fopen("akun.txt","w");
	fclose(file2);
	FILE *file = fopen("akun.txt","r");
    }
		read=recv(clientSocket,data,1024,0);
    char found = 0;
    while (fscanf(file, "%s", secret) != EOF) {
	if (!strcmp(secret, data)) {
	    found = 1;
	    break;
	}
    }
    if(found) {
	printf("Auth success\n");
	strcpy(output,"success");
		send(clientSocket,output,1024,0);
    } else {
	printf("Auth Failed\n");
	strcpy(output,"failed");
		send(clientSocket,output,1024,0);
    }
    fclose(file); 
}
```
Pada saat client mengirimkan username dan password, server akan membuka data pada akun.txt, dan membandingkan masing-masing data yang ada, apabila ditemukan, maka login sukses. Apabila akun.txt belum ada, maka akan dibuat terlebih dahulu, tetapi karena kosong, tetap tidak dapat login.

Register

```
if(strcmp(data,"Register") == 0){
			FILE *file2 = fopen("akun.txt","a");
            read=recv(clientSocket,data,1024,0);
            data[read]='\0';
            fprintf(file2,"%s",data);
            fprintf(file2,"\n");
            strcpy(output,"success");
            fclose(file2);
            FILE *file = fopen("akun.txt","r");
            while (fscanf(file, "%s", secret) != EOF) {
                printf("%s\n",secret);
            }
            fclose(file);
            send(clientSocket,output,1024,0);
}
```
Pada saat register, apabila akun.txt belum ada, akan dibuat terlebih dahulu kemudian akan di cetak pada akun.txt yaitu username dan password. Kemudian diprint semua data akun dan password nya pada terminal server untuk mengecek apakah sudah tercatat atau belum.

FIND MATCH

Karena codingan cukup panjang, maka silahkan dibuka url di atas. Penjelasannya sebagai berikut:

Pertama, server menerima sinyal bahwa ada satu client yang ingin bermain, kemudian sinyal tersebut dibiarkan sampai ada client lain yang juga ingin bermain. Setelah menemukan dua orang pemain, maka masing masing client diberi sinyal untuk memulai permainan. Setelah itu, kedua client langsung bermain tap tap.

Apabila pada saat salah satu pemain melakukan tap, pemain satunya akan dikirimkan sinyal untuk menampilkan bahwa power nya dikurangi 10. Pemain yang berhasil melakukan tap, akan ditampilkan hit!! pada terminal. Setelah salah satu pemain powernya = 0, maka permainan dihentikan.

Pada program server ini, menggunakan thread untuk menghandle banyak client secara bersamaan, masing-masing client satu thread.

## No 3

### Source Code : [3](https://github.com/rifkiirawan/SoalShiftSISOP20_modul3_F02/blob/master/soal3/soal3.c)

Pada soal ini akan mengkategorikan file sesuai dengan ekstensinya masing-masing, jika argumen `-f` dimasukkan, maka file yang diinputkan setelah argumen akan dikategorikan, jika argumen `-d` dimasukkan, maka file yang terdapat pada direktori yang diinputkan setelah argumen akan dikategorikan, jika argumen `\*` dimasukkan, maka semua file yang terdapat pada direktori yang sedang ditempati akan dikategorikan.

Pada tiap thread akan mengambil ekstensi dari tiap file dengan menggunakan
``
char* ext = strrchr(d->name,'.');
``

Pada kodingan terdapat fungsi `void lowcase` yang berfungsi agar nama filenya tidak case sensitive. Untuk fungsi `void makefile` berfungsi untuk membuat folder sesuai dengan ekstensi yang dimiliki oleh file. Untuk fungsi `void* move` berfungsi untuk memindahkan file ke folder yang telah dibuat.

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

#### 4c. Mencari jumlah file yang ada pada direktori saat ini. 

Seperti yang di instruksikan pada soal, fungsi wc berfungsi untuk menghitung jumlah file yang ada pada direktori yang sedang berjalan.
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

## Authors

Created by:

[Rifki Aulia Irawan 142] (https://github.com/rifkiirawan)

[Evelyn Tjitrodjojo 99] (https://github.com/marsellaeve)
	- Kesulitan dalam mengerti soal, kepanjangan sangat sangat kepanjangan (apalagi nomor 1).
	- Soal dalam bentuk permainan, karena saya tidak pernah main, kesulitan memahami cara main, bentuk permainan, dll.
