#include <pthread.h>
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define SERVER_ADDRESS  "192.168.43.231"     /* server IP */
//#define SERVER_ADDRESS "192.168.246.131"     /* IP, only IPV4 support  */
#define PORT            8080 

struct Frame 
{
	unsigned char sof;	// start of frame=0xAA | 170 ASCII		0:cliente | 1:despachado 
	unsigned char sensor;  // 01 | 02 | 03 |  FF
	unsigned char axis;	// x:01 | y:02 | z:03 | 04
	int8_t checksum;  // sum calculated from SOF+ sensor+ Axis
};

/* Test sequences */
char buf_tx[1024];
char buf_rx[1024];                /* receive buffer */
pthread_mutex_t socketMutex = PTHREAD_MUTEX_INITIALIZER;
 
 
/* This clients connects, sends a text and disconnects */
int main() 
{ 
    int sockfd;
    //unsigned char sof_input = atoi(argv[1]);
    //unsigned char sensor_input = atoi(argv[2]);
    //unsigned char axis_input = atoi(argv[3]);
    
    struct sockaddr_in servaddr; 
    struct Frame command_frame = {0};
    //command_frame.checksum = (sizeof(command_frame.sof)+ sizeof(command_frame.sensor+ sizeof(command_frame.axis);
    
    printf("%li :",sizeof(command_frame));
    printf("-> sof: %i\n",command_frame.sof);
    printf("-> sensor: %i\n",command_frame.sensor);
    printf("-> axis: %i\n",command_frame.axis);
    
    /* Socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        printf("CLIENT: socket creation failed...\n"); 
        return -1;  
    } 
    else
    {
        printf("CLIENT: Socket successfully created..\n"); 
    }
    
    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, PORT */
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr( SERVER_ADDRESS );
    servaddr.sin_port = htons(PORT); 
  
    /* try to connect the client socket to server socket */
    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        printf("connection with the server failed...\n");
        return -1;
    } 
    printf("connected to the server..\n");
        
    // FIRST MESSAGE
	// READ()
	recv(sockfd, buf_rx, sizeof(buf_rx),0);
	printf("[SERVER]: %s \n", buf_rx);
  
    /* hilo 1*/
    while(1)
    {
    	// 
    
    	// READ KEYBOARD
		fgets(buf_tx,sizeof(buf_tx),stdin);
		// LOCK RESOURCES
    	pthread_mutex_lock(&socketMutex);
    	// WRITE()
		send(sockfd, buf_tx, sizeof(buf_tx),0);
		// READ()
		recv(sockfd, buf_rx, sizeof(buf_rx),0);
		printf("[SERVER]: %s \n", buf_rx);
		// UNLOCK RESOURCES
        pthread_mutex_unlock(&socketMutex);
        // SYNCHRONIZE
		sleep(1);
		
    }
   
       
    /* close the socket */
    close(sockfd); 
} 


