#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>    
#include <stdlib.h>  
#include <pthread.h>  

#include <glib.h>


#define MAX 5

#define MAX_LISTEN_NUM 5  
#define SEND_BUF_SIZE 128  
#define RECV_BUF_SIZE 128  
#define LISTEN_PORT 10005

pthread_t thread[2];
pthread_mutex_t mut1;
pthread_mutex_t mut2;

int number=0;

GTimer * timer;


void *thread1(void *ptr)
{
	int i;
	printf ("thread1 : I'm thread 1\n");
	g_timer_start(timer);
	for (i = 0; i < MAX; i++)
	{
		pthread_mutex_lock(&mut1);
		printf("thread1 : number = %d\n",number);
			number++;
			sleep(1);
		pthread_mutex_unlock(&mut1);
	}
	printf("thread1 :waiting?\n");
	pthread_exit(NULL);
}


void *thread2(void *ptr)
{
	int i;
	printf("thread2 : I'm thread 2\n");
	for (i = 0; i < MAX; i++)
	{
		pthread_mutex_lock(&mut1);
		printf("thread2 : number = %d\n",number);
			number++;
			sleep(1);
		pthread_mutex_unlock(&mut1);
	}
	g_timer_stop (timer);
	printf("thread2 :waiting？\n");
	pthread_exit(NULL);
}


void thread_create(void)
{
	int temp;
	memset(&thread, 0, sizeof(thread));          
	/*create thread*/
	if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0)       
		printf("create thread1 faild!\n");
	else
		printf("thread1 created,%d\n",temp);
	if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0)  
		printf("create thread2 faild");
	else
		printf("thread2 created\n");
}


void thread_wait(void)
{
	/*wait for thread1,2 exit*/
	if(thread[0] !=0) {                   
		pthread_join(thread[0],NULL);
		printf("thread1 exit\n");
	}
	if(thread[1] !=0) {                
		pthread_join(thread[1],NULL);
		printf("thread2 exit\n");
	}
}

void *rec_data(void *fd)  
{  
	int client_sockfd;  
	int n,bufsize;
	char buff[2048];
	printf("main thread tid = %u\n", pthread_self());
	client_sockfd=*((int*)fd);  
	while(1)
	{
		recv(client_sockfd, &bufsize, 1, 0);
		n = recv(client_sockfd, buff, bufsize, 0);
		buff[n] = '\0';
		printf("recv msg from client: %s\n", buff);
		memset(&buff,0,sizeof(buff));
	}
	
	close(client_sockfd);  
}  



int main(){

	gulong* se;
	gdouble elapsed_time;
	
	pthread_mutex_init(&mut1,NULL);
	pthread_mutex_init(&mut2,NULL);
	timer = g_timer_new ();
		
	thread_create();
	
	thread_wait();
	
	elapsed_time = g_timer_elapsed (timer,se);
	
	printf("time elapsed: %lf\n", elapsed_time);
	
	printf("number = %d\n",number);
	return 0;
}

//int main()
//{
////	pthread_mutex_init(&mut1,NULL);
////	pthread_mutex_init(&mut2,NULL);
////	printf("createing threads\n");
////	thread_create();
////	//printf("thread[0]: %d\n",thread[0]);
////	printf("waiting for thread1,thread2 exit\n");
////	thread_wait();
//
//	int listen_sock = 0;  
//	int connfd  = 0;  
//	struct sockaddr_in hostaddr;  
//	struct sockaddr_in clientaddr;  
//	int socklen = sizeof(clientaddr);
//
//	memset((void *)&hostaddr, 0, sizeof(hostaddr));  
//	memset((void *)&clientaddr, 0, sizeof(clientaddr));  
//	hostaddr.sin_family = AF_INET;  
//	hostaddr.sin_port = htons(LISTEN_PORT);  
//	hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);  
//	listen_sock = socket(AF_INET, SOCK_STREAM, 0);  
//	if(listen_sock < 0)  
//	{  
//		perror("create socket failed");  
//		exit(1);  
//	}  
//	if(bind(listen_sock, (struct sockaddr *)&hostaddr, sizeof(hostaddr)) < 0)  
//	{
//		perror("bind socket failed");  
//		exit(1);  
//	}  
//	if(listen(listen_sock, MAX_LISTEN_NUM) < 0)  
//	{  
//		perror("listen failed");  
//		exit(1);  
//	}  
//
//	printf("listen\n");
//	while(1)  
//	{  
//		
//		connfd  = accept(listen_sock, (struct sockaddr *)&clientaddr,  (socklen_t *)&socklen);  
//		if(connfd  < 0)  
//		{
//			perror("accept failed");  
//			exit(1);  
//		}
//		if(pthread_create(&thread[0], NULL, rec_data, &connfd) != 0){
//			perror("pthread_create");  
//			continue;  
//		}          
//	}
//
//	shutdown(connfd,2);
//	shutdown(listen_sock,2);
//	return 0;
//}
//

