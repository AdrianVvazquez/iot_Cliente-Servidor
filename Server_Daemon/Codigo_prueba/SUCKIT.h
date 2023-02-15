#ifndef SUCKIT
#define SUCKIT
/*standard symbols */
#include <unistd.h>  

/* sockets */
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>

/* strings / errors*/
#include <errno.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

/* server parameters */
#define PORT           8080              /* port */
#define SERV_HOST_ADDR "192.168.0.21"    /* IP, only IPV4 support  */
#define BUF_SIZE       150               /* Buffer rx, tx max size  */
#define BACKLOG        5                 /* Max. client pending connections  */


int Crear_Socket(){
	int sockfd;
    unsigned int len;

	struct sockaddr_in serverAddr;
	char buffer[1024];

    int len_rx;                           /* received and sent length, in bytes */
    char buff_tx[BUF_SIZE] = "Hello client, this is The server. Choose an option\n [1]Accelerometer\n[2]Magnetometer\n[3]Gyroscope\n[4]All sensors";

    /*Creacion del socket*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0){
		printf("[SERVER]: Error con la conexion.\n");
		exit(1);
	} else{
	    printf("[SERVER]: El socket ha sido creado.\n");
    }

    /*Configuracion del socket*/
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);

    /*Bind*/
    if ((bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) != 0){
		printf("[SERVER-ERROR]: Error in binding.\n");
		exit(1);
	} else{
        if(listen(sockfd, 10) == 0){
		    printf("[Server]: Escuchando en el puerto: %d\n", PORT);
	    }
    }
    return sockfd;
}

int Escuchar_Socket(int sockfd){
    int connfd;
    struct sockaddr_in clientAddr;

    connfd = accept(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));

    return connfd;
}

int Despachar_Socket(int connfd){
    char buff_rx[BUF_SIZE];
    int len_rx;

    printf("[Server]: Conexión aceptada %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(newAddr.sin_port));
    while(1){  
        /* read client message, copy it into buffer */
        len_rx = read(connfd, buff_rx, sizeof(buff_rx));  
            
        if(len_rx == -1){
            fprintf(stderr, "[SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
        } else if(len_rx == 0){
            printf("[SERVER]: client socket closed \n\n");
            close(connfd);
            break; 
        } else{
            write(connfd, buff_rx, strlen(buff_tx));
            printf("[SERVER]: %s \n", buff_rx);
        }
    }
	close(connfd);
	return 0;
}
#endif //SUCKIT