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
#include <string.h> 
/* threads */
#include <pthread.h>

/* server parameters */
#define SERV_PORT       8080              /* port */
#define SERV_HOST_ADDR "192.168.246.131"     /* IP, only IPV4 support  */
//#define SERV_HOST_ADDR "192.168.43.231"     /* IP, only IPV4 support  */
#define BUF_SIZE        150               /* Buffer rx, tx max size  */
#define BACKLOG         5                 /* Max. client pending connections  */
//#define EXIT 			0

//struct Json_data 
//{
//	char exit[4];
//};


int main()          /* input arguments are not used */
{ 
    int sockfd, connfd ;  /* listening socket and connection socket file descriptors */
    unsigned int len;     /* length of client address */
    struct sockaddr_in servaddr, client; 
    //struct Json_data json = {"exit"};
    
	pthread_mutex_t socketMutex = PTHREAD_MUTEX_INITIALIZER;
    
    int  len_tx;                     /* received and sent length, in bytes */
    char buff_tx[BUF_SIZE] = "Hello client, this is The server. Choose an option\n[1]Accelerometer\n[2]Magnetometer\n[3]Gyroscope\n[4]All sensors";
    char buff_rx[BUF_SIZE];   /* buffers for reception  */
    
	/* Identifier */
	//pthread_t tid;
	/* Attributes */
	//pthread_attr_t attr;
    /* thread init */
    //pthread_attr_init(&attr);
     
    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) 
    { 
        printf("[SERVER-error]: socket creation failed. %d\n", errno);
        return -1;
    } 
    else
    {
        printf("Status: Socket successfully created...\n"); 
    }
    
    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));
  
    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family      = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR); 
    servaddr.sin_port        = htons(SERV_PORT); 
    
    
    /* Bind socket */
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) 
    { 
        printf("[SERVER-error]: socket bind failed. %d: %s\n", errno, strerror(errno));
        return -1;
    } 
    else
    {
        printf("Status:  Socket successfully binded. \n");
    }
  
    // LISTEN
    if ((listen(sockfd, BACKLOG)) != 0) 
    { 
        printf("[SERVER-error]: socket listen failed. %d: %s\n", errno, strerror(errno));
        return -1;
    } 
    else
    {
        printf("Status: Listening on SERV_PORT %d \n", ntohs(servaddr.sin_port) ); 
    }
    
    len = sizeof(client); 
    
// HILO 1
	/* Accept the data from incoming sockets in a iterative way */
	while(1)
	{
		// ACCEPT
		connfd = accept(sockfd, (struct sockaddr *)&client, &len);
        if (connfd < 0) 	// file descriptor < 0
        { 
            printf("[SERVER-error]: connection not accepted. %d: %s\n", errno, strerror(errno));
            return -1;
        } 
        else
        {     // file descriptor != 0
        	// ADD CONECTION TO LIST
        	printf("Status: Connection accepted.\n\n");
// EXIT HILO 1
			while(1)
			{
				// WRITE()
				len_tx = send(connfd, buff_tx, strlen(buff_tx),0);
				printf("debug:write returns file descriptor: %i\n",len_tx);
		            
		        if(len_tx == -1)
		        {
		            printf("[SERVER-error]: connfd cannot write. %d: %s\n", errno, strerror(errno));
		            break;
		        }
		        else if(len_tx == 0) /* if length is 0 client socket closed, then exit */
		        {
		            printf("[SERVER]: client socket closed \n\n");
		            close(connfd);
		            break; 
		        }
		        else
		        {
// HILO 2
			        /* only if first write was succeed */
					//while(1) /***** read data from a client socket till it is closed *****/ 
					//{
						// LOCK RESOURCES
						pthread_mutex_lock(&socketMutex);
						// READ()
			            recv(connfd, buff_rx, sizeof(buff_rx),0);
				        printf("[CLIENT]: %s \n", buff_rx);
			            if(strncmp(buff_rx,"1",1)==0)
			            {
				            send(connfd, "accelerometer", sizeof(buff_rx),0);	
			            } else
			            if(strncmp(buff_rx,"2",1)==0)
			            {
				            send(connfd, "magnetometer", sizeof(buff_rx),0);	
			            } else
			            if(strncmp(buff_rx,"3",1)==0)
			            {
				            send(connfd, "gyroscope", sizeof(buff_rx),0);	
			            } else
			            if(strncmp(buff_rx,"4",1)==0)
			            {
				            send(connfd, "all", sizeof(buff_rx),0);	
			            } else
			            {
					        // WRITE()
					        send(connfd, buff_rx, sizeof(buff_rx),0);
							// UNLOCK RESOURCES
				        }
						pthread_mutex_unlock(&socketMutex);
				        close(connfd);
		            //}
		        }
// EXIT HILO 2
		    }				
		}
    }    
}


