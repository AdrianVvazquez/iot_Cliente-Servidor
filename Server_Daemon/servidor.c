#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define IP "192.168.43.231"
#define BUFFER 1024
#define MAX_CONN 2

int client_n = 0;
int client_list[MAX_CONN];

char buff_tx[BUFFER] = "Conectado al Servidor H0=OoolaA44a\nSeleccione:\n1) uno\n2) dos\n";
char buff_rx[BUFFER];

void *lupe(void *param);

int main()
{
    int test_conn;

    int sockfd, binded;
    struct sockaddr_in serverAddr;

    int connfd;
    struct sockaddr_in newAddr;

    socklen_t addr_size;

    pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

    bzero(client_list, MAX_CONN);

    /*Crear socket*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        printf("[SERVER]: Error in connection.\n");
        exit(1);
    }
    printf("[SERVER]: Server Socket is created.\n");

    /*Configurar socket*/
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IP);

    /*Asociar a direccion ip*/
    binded = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (binded < 0)
    {
        printf("[SERVER]: Error in binding.\n");
        exit(1);
    }
    printf("[SERVER]: Bind to port %d\n", PORT);

    /*Escuchar socket*/
    if (listen(sockfd, MAX_CONN) == 0)
    {
        printf("[SERVER]: Listening....\n");
    }
    else
    {
        printf("[SERVER]: Error in listening.\n");
    }

// HILO 2 DESPACHA
    pthread_create(&tid, &attr, lupe, 10);

// HILO 1 AGREGA CONN A LA LISTA
    /*Aceptar conexiónes*/
    while (1)
    {
        /*aceptar cliente */
        if (client_n < MAX_CONN) {
            client_list[client_n] = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);
            printf("\n[SERVER]: cliente: %d\n\n", client_list[client_n]);
            test_conn = send(client_list[client_n], buff_tx, strlen(buff_tx), 0);
            client_n++;
        } else {
            printf("[SERVER]: Servidor Lleno\n");
            sleep(1);
            continue;
        }
    }
    return 0;
}

void *lupe(void *param)
{
    int i;

    while(1) {
        //connfd != 0
        for (i = 0; i < MAX_CONN; i++) {
            // if (test_conn == -1) {
            //     printf("[SERVER-error]: connfd cannot write.\n");
            //     break;
            // }
            // else if(test_conn == 0) /* if length is 0 client socket closed, then exit */
            // {
            //     printf("[SERVER]: client socket [%d] closed \n\n", client_list[i]);
            //     close(client_list[i]);
            //     client_list[i] = 0;
            //     client_n --;
            //     continue;
            // } else {

            printf("[DEBUG]: hola %d %d\n", i, client_list[i]);
            sleep(1);
            if (client_list[i] != 0){
                bzero(buff_rx, BUFFER);
                recv(client_list[i], buff_rx, 1024, 0);

                printf("[DEBUG]: adios %d %d\n", i, client_list[i]);

                /*recibe peticion del cliente y la atiende*/
                if (strncmp(buff_rx,"1",1)==0) {
                    send(client_list[i], "accelerometer", sizeof(buff_tx),0);	
                } else
                if (strncmp(buff_rx,"2",1)==0) {
                    send(client_list[i], "magnetometer", sizeof(buff_tx),0);	
                } else
                if (strncmp(buff_rx,"3",1)==0) {
                    send(client_list[i], "gyroscope", sizeof(buff_tx),0);	
                } else
                if (strncmp(buff_rx,"4",1)==0) {
                    send(client_list[i], "all", sizeof(buff_tx),0);	
                } else {
                    // WRITE()
                    send(client_list[i], buff_rx, sizeof(buff_tx),0);
                    // UNLOCK RESOURCES
                }
            }
        }
    }
    sleep(1);
}