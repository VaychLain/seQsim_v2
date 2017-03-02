#include <stdio.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <sys/types.h>   
#include <arpa/inet.h>  
#include <unistd.h>  
#include <netinet/in.h>  
#include <syslog.h>  
#include <errno.h>  
#include <stdlib.h>


#define MAX_LISTEN_NUM 5  
#define SEND_BUF_SIZE 100  
#define RECV_BUF_SIZE 100  
#define SERVER_PORT 1010  


int main()  
{  
    int sock_fd = 0;
    int i;
    char sendline[2048]="Client Query test";
    struct sockaddr_in ser_addr;  
    
	for(i=0;i<10;i++){
    memset(&ser_addr, 0, sizeof(ser_addr));  
    ser_addr.sin_family = AF_INET;  
    inet_aton("127.0.0.1", (struct in_addr *)&ser_addr.sin_addr);  
    ser_addr.sin_port = htons(SERVER_PORT);  
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);  
    if(sock_fd < 0)  
    {  
        perror("create socket failed") ; 
        exit(1);  
    }  
    
	if(connect(sock_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)  
    {  
        perror("connect socket failed");  
        exit(1);  
    }  

    printf("send msg to server: \n");
    //fgets(sendline, 4096, stdin);
    if( send(sock_fd, sendline, strlen(sendline), 0) < 0)
    {
    printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
    exit(0);
    }
	close(sock_fd);  
	sleep(1);
	}

	
      
}  