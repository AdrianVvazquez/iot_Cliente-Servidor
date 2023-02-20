#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define SERVER_ADDRESS  "192.168.246.131"     /* server IP */
#define PORT            8080 

struct Frame 
{
	unsigned char sof;	// start of frame=0xAA | 170 ASCII
	unsigned char sensor;  // 01 | 02 | 03 | FF
	unsigned char axis;	// x:01 | y:02 | z:03 | 04
	int8_t checksum;  // sum calculated from SOF+ sensor+ Axis
};

/* Test sequences */
char buf_tx[] = "Hello server. I am a client";
char buf_rx[150];                /* receive buffer */
 
 
/* This clients connects, sends a text and disconnects */
int main() 
{ 
    int sockfd;
    //unsigned char sof_input = atoi(argv[1]);
    //unsigned char sensor_input = atoi(argv[2]);
    //unsigned char axis_input = atoi(argv[3]);
    
    struct sockaddr_in servaddr; 
    //struct Frame command_frame = {0};
    //command_frame.checksum = (sizeof(command_frame.sof)+ sizeof(command_frame.sensor+ sizeof(command_frame.axis);
    
    //printf("%li :",sizeof(command_frame));
    //printf("-> sof: %i\n",command_frame.sof);
    //printf("-> sensor: %i\n",command_frame.sensor);
    //printf("-> axis: %i\n",command_frame.axis);

    
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
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        printf("connection with the server failed...\n");  
        return -1;
    } 
    
    printf("connected to the server..\n"); 
  
    /* send test sequences*/
    while(1)
    {
		write(sockfd, buf_tx, sizeof(buf_tx));     
		read(sockfd, buf_rx, sizeof(buf_rx));
		printf("[CLIENT]: %s \n", buf_rx);
		fgets(buf_tx,sizeof(buf_tx),stdin);
		write(sockfd, buf_tx, sizeof(buf_tx));
		
    }
   
       
    /* close the socket */
    close(sockfd); 
} 
