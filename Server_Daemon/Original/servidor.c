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

typedef struct client_conn {
    int fd;
    struct client_conn* next;
} client_conn_t;

void print_node_list(client_conn_t *current_conn){
    client_conn_t *temp = current_conn;
    printf("Lista de clientes\n\n");

    while(temp != NULL){
        printf("fd: %d next: %d\n", temp->fd, temp->next);
        temp = temp->next;
    }
}

client_conn_t *create_new_node(client_conn_t *current, int fd){
    client_conn_t *new_node = malloc(sizeof(client_conn_t));
    new_node->fd = fd;
    new_node->next = current;

    return new_node;
}

int main(){
    /*variables para pruebs*/
    int tiempo = 0, new_conn;
    client_conn_t *current_conn = NULL, *tmp;

	int sockfd, binded;
	struct sockaddr_in serverAddr;

	int connfd;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[BUFFER];

    /*Crear socket*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
	if(sockfd < 0){
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
	binded = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(binded < 0){
		printf("[SERVER]: Error in binding.\n");
		exit(1);
	}
	printf("[SERVER]: Bind to port %d\n", PORT);

    /*Escuchar socket*/
	if(listen(sockfd, MAX_CONN) == 0){
		printf("[SERVER]: Listening....\n");
	} else{
		printf("[SERVER]: Error in listening.\n");
	}

	while(1){
        /*guardar en arreglo*/
        new_conn = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		tmp = create_new_node(current_conn, new_conn);
        current_conn = tmp;
        print_node_list(current_conn);

	// 	if(conn_list[0].fd < 0){
	// 		exit(1);
	// 	} else{
            
    //         printf("client [%d] Accepted from %s:%d\n", conn_list[0].fd, inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
    //         printf("sizeof: %d contenido: %d\n\n", sizeof(conn_list[0].fd), &conn_list[0].fd);
    //         /*posible hilo*/
    //         // while(1){
    //         //     bzero(buffer, sizeof(buffer));
    //         //     recv(conn_list[0].fd, buffer, 1024, 0);
    //         //     printf("Tiempo: [%d] buff: [%s]", tiempo, buffer);
    //         //     sleep(1);
    //         //     if(strcmp(buffer, ":exit") == 0){
    //         //         printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
    //         //         break;
    //         //     }else{
    //         //         printf("Client: %s\n", buffer);
    //         //         send(conn_list[0].fd, "ok", strlen(buffer), 0);
    //         //     }
    //         //     tiempo++;
    //         // }
    //     }
    //     sleep(2);
	}

	// close(conn_list[0].fd);


	return 0;
}