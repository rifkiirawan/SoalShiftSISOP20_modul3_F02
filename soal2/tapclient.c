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

int main(){
    int halaman=0;
	int clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) return 0;

	printf("Connection established ............\n");

	// pthread_t thread;
	// pthread_create(&thread, NULL, doRecieving, (void *) &clientSocket );

	while(1){
		char input[30],output[1024];
        char Username[100];
        char Password[100];
        char Data[500];
        if(halaman==0){
            memset(output,0,sizeof output);
            system("clear");
            printf("1. Login\n2. Register\nChoices : ");
            scanf("%s",input);
            send(clientSocket,input,1024,0);
            if(strcmp(input,"Login") == 0){
                printf("Username : ");
                scanf("%s",Username);
                printf("Password : ");
                scanf("%s",Password);
                sprintf(Data,"Username:%s|Password:%s",Username,Password);
                send(clientSocket,Data,500,0);
                recv(clientSocket,output,1024,0);
                system("clear");
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
            if(strcmp(input,"Register") == 0){
                printf("Username : ");
                scanf("%s",Username);
                printf("Password : ");
                scanf("%s",Password);
                sprintf(Data,"Username:%s|Password:%s",Username,Password);
                send(clientSocket,Data,500,0);
                recv(clientSocket,output,1024,0);
                system("clear");
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
        }
        if(halaman==1){
            // system("clear");
            char dummy;
            printf("1. Find Match\n2. Logout\nChoices : ");
            scanf("%s%c",input,&dummy);
            if(strcmp(input,"Logout")==0){
                halaman=0;
                continue;
            }
            if(strcmp(input,"Find")==0){
                send(clientSocket,input,500,0);
                printf("Waiting for opponent.....\n");
                int read=recv(clientSocket,output,1024,0);
                system("clear");
                printf("Game dimulai silahkan tap ​tap​ secepat mungkin!!\n");
                output[read]='\0';
                system("stty raw");
                while(1){
                    input[0]=getchar();
                    input[1]='\0';
                    send(clientSocket,input,500,0);
                    int read=recv(clientSocket,output,1024,0);
                    output[read]='\0';
                    if(!strstr(output,"hit!!")){
                        system("stty cooked");
                        system("clear");
                        printf("%s\n",output);
                        break;
                    }
                    system("clear");
                    printf("%s\n",output);
                }
            }
        }
	}
}