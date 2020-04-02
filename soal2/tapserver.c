#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int clientCount = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct client{

	int index;
	int sockID;
	struct sockaddr_in clientAddr;
	int len;

};

struct client Client[1024];
pthread_t thread[1024];
int player1[1024];
int player2[1024];
int cnt1,cnt2;

void * doNetworking(void * ClientDetail){

	struct client* clientDetail = (struct client*) ClientDetail;
	int index = clientDetail -> index;
	int clientSocket = clientDetail -> sockID;

	printf("Client %d connected.\n",index + 1);

	while(1){

        char data[1024],secret[500];
		int read = recv(clientSocket,data,1024,0);
		data[read] = '\0';
		char output[1024];
        memset(output,0,sizeof output);
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
        if(strcmp(data,"Find") == 0){
            int cnt;
            int play,enem;
			if(cnt1==cnt2){
                player1[cnt1]=100;
                cnt=cnt1++;
                play=1;
                enem=2;
            }
            else {
                player2[cnt2]=100;
                cnt=cnt2++;
                play=2;
                enem=1;
            }
            strcpy(output,"success");
            while (cnt1!=cnt2) {
            }
            send(clientSocket,output,1024,0);
            while(1){
                read=recv(clientSocket,data,500,0);
                data[read]='\0';
                if(strcmp(data," ")==0){
                    if(play==1){
                        player2[cnt]-=10;
                    }
                    else{
                        player1[cnt]-=10;
                    }
                }
                if(player2[cnt]<=0){
                    if(play==1){
                        strcpy(output,"Game berakhir kamu menang");
                        send(clientSocket,output,1024,0);
                    }
                    if(play==2){
                        strcpy(output,"Game berakhir kamu kalah");
                        send(clientSocket,output,1024,0);
                    }
                    break;
                }
                else if(player1[cnt]<=0){
                    if(play==2){
                        strcpy(output,"Game berakhir kamu menang");
                        send(clientSocket,output,1024,0);
                    }
                    if(play==1){
                        strcpy(output,"Game berakhir kamu kalah");
                        send(clientSocket,output,1024,0);
                    }
                    break;
                }
                sprintf(output,"%d\nhit!!",play==1?player1[cnt]:player2[cnt]);
                // strcpy(output,"hit!!");
                send(clientSocket,output,1024,0);
            }

		}

	}

	return NULL;

}

int main(){
    cnt1=cnt2=0;
	int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = htons(INADDR_ANY);


	if(bind(serverSocket,(struct sockaddr *) &serverAddr , sizeof(serverAddr)) == -1) return 0;

	if(listen(serverSocket,1024) == -1) return 0;

	printf("Server started listenting on port 8080 ...........\n");

	while(1){
        Client[clientCount].sockID = accept(serverSocket, (struct sockaddr*) &Client[clientCount].clientAddr, &Client[clientCount].len);
		Client[clientCount].index = clientCount;

		 pthread_create(&thread[clientCount], NULL, doNetworking, (void *) &Client[clientCount]);

		clientCount ++;
 
	}

	for(int i = 0 ; i < clientCount ; i ++)
		pthread_join(thread[i],NULL);

}