//#define SECURED_STRONG
//#define SECURED_NORMAL
//#define NON_SECURED

#include "RSLTcache.h"
#include "../helps.h"
#include "../globals.h"

void *rec_data(void *fd)  
{  
	int client_sockfd;  
	int n,bufsize,i,idx;
	char buff[2048];
	char* begin="ss,ss,ss";
	
	std::string pushdate;
	printf("main thread tid = %u\n", pthread_self());
	client_sockfd=*((int*)fd);  
	int flag=1;
	while (1){
		idx=i%2;
		i++;
		if(flag==1) 
		{
			printf("recv_data lock %d\n", idx);
			n = recv(client_sockfd, buff, 1, 0);
			bufsize = (int)buff[0];
			memset(&buff,0,sizeof(buff));
			n = recv(client_sockfd, buff, bufsize, 0);
			buff[n] = '\0';
			pushdate = buff;
			count_push++;
			std::cout <<"Enqueue " << idx+1<<": "<< pushdate<<std::endl;
			
			if (count_push==1){
				g_timer_start(timer);
			}
		}
		
		if(pthread_mutex_trylock(mut_arr[idx])==0)
		{
#ifdef SEC_HIGH
			std::string node_addr = pub_CreateQNode(pushdate);
			pub_AddNodeToQ(&qgrp, qgrp.m_pub_qgroup[idx], node_addr);
#else
			queue[idx].push(pushdate);
#endif
			pthread_mutex_unlock(mut_arr[idx]);
			printf("recv msg from client: %s\n", buff);
			memset(&buff,0,sizeof(buff));
			flag=1;
		}
			else 
			{
				std::cout << "Can't lock queue "<<idx+1<<std::endl;
				flag =0;
			}
	}
	close(client_sockfd);  
}  

void *pushThread(void *ptr)
{
	
	int listen_sock = 0;  
	int connfd  = 0;  
	struct sockaddr_in hostaddr;  
	struct sockaddr_in clientaddr;  
	int socklen = sizeof(clientaddr);
	int flag=1,len=sizeof(int);

	memset((void *)&hostaddr, 0, sizeof(hostaddr));  
	memset((void *)&clientaddr, 0, sizeof(clientaddr));  
	hostaddr.sin_family = AF_INET;  
	hostaddr.sin_port = htons(LISTEN_PORT);  
	hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);  
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);  
	if(listen_sock < 0)  
	{  
		perror("create socket failed");  
		exit(1);  
	}  
	if(setsockopt(listen_sock,SOL_SOCKET,SO_REUSEADDR,&flag,len)==-1)
	{
		perror("setsockopt");
		exit(1);
		}
	if(bind(listen_sock, (struct sockaddr *)&hostaddr, sizeof(hostaddr)) < 0)  
	{
		perror("bind socket failed");  
		exit(1);  
	}  
	if(listen(listen_sock, MAX_LISTEN_NUM) < 0)  
	{  
		perror("listen failed");  
		exit(1);  
	}  

	printf("listen port: %d\n",LISTEN_PORT);
	while(1)  
	{  
		
		connfd  = accept(listen_sock, (struct sockaddr *)&clientaddr,  (socklen_t *)&socklen);  
		if(connfd  < 0)  
		{
			perror("accept failed");  
			exit(1);  
		}
		if(pthread_create(&thread[0], NULL, rec_data, &connfd) != 0){
			perror("pthread_create");  
			continue;  
		}          
	}
}





void *popThread(void *ptr)
{
	gulong* se;
	gdouble elapsed_time;
	
	int sock_fd = 0;
	char sendline[2048];
	char bufsize;
	struct sockaddr_in ser_addr;
	std::string stemp;
	std::vector<std::string> splitted_str;
	int i=1;
		
	memset(&sendline, 0, sizeof(sendline)); 
	
	memset(&ser_addr, 0, sizeof(ser_addr));  
	ser_addr.sin_family = AF_INET;  
	inet_aton("172.17.0.6", (struct in_addr *)&ser_addr.sin_addr);  
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
	
	while(1){
		i++;
		i=i%2;
		if(pthread_mutex_trylock(mut_arr[i])==0)
		{
			//printf("pop_data lock %d\n", i);
#ifdef SEC_HIGH
			while (pub_GetQSizeByShadowAddr(&qgrp,qgrp.m_pub_qgroup[i].c_str()))
			{
				printf("%d\n",i);
				stemp = pub_Dequeue(&qgrp, qgrp.m_pub_qgroup[i]);
				split_string(stemp, splitted_str, "|");
				strcpy(sendline,splitted_str[1].c_str());
				std::vector<std::string>().swap(splitted_str);
#else
			while (!queue[i].empty())
			{
				strcpy(sendline,queue[i].front().c_str());
				queue[i].pop();
#endif
				printf("pop from queue: %d",i+1);
				std::cout << ' ' << sendline << std::endl;
				bufsize = (char)strlen(sendline);
				
				//timer module
				count_pop++;
				if (count_pop==TEST_CASE_NUM)
				{
					g_timer_stop (timer);
					elapsed_time = g_timer_elapsed (timer,se);
					printf("time elapsed: %lf\n", elapsed_time);
					timeToFile("rsltcache.txt", elapsed_time);
					count_pop = 0;
					count_push = 0;
					//sleep(10);
				}
				
				if(send(sock_fd,&bufsize,1, 0) < 0)
				{
					perror("send msg error");
					exit(0);
				}	
				if(send(sock_fd,sendline, strlen(sendline), 0) < 0)
				{
					perror("send msg error");
					exit(0);
				}	
				

				memset(&sendline,0,sizeof(sendline));
				//sleep(1);
			}
			pthread_mutex_unlock(mut_arr[i]);
			//sleep(1);
		}
		else 
		{
			//printf("can't lock %d\n",i);
		}
	}
	close(sock_fd);
}


void thread_create(void)
{
	int temp;
	memset(&thread, 0, sizeof(thread));          
	/*create thread*/
	
	if((temp = pthread_create(&thread[1], NULL, pushThread, NULL)) != 0)  
		printf("create pushThread faild",temp);
	else
		printf("pushThread created\n");
		
	sleep(2);
	
	if((temp = pthread_create(&thread[0], NULL, popThread, NULL)) != 0)       
		printf("create popThread faild!\n");
	else
		printf("popThread created,%d\n",temp);
}


void thread_wait(void)
{
	/*wait for thread1,2 exit*/
	if(thread[0] !=0) {                   
		pthread_join(thread[0],NULL);
		printf("pushThread exit\n");
	}
	if(thread[1] !=0) {                
		pthread_join(thread[1],NULL);
		printf("popThread exit\n");
	}
}



void testbuf(PQ_GROUP q_grp, int n){
		
	for (int i=0; i<n; i++){
		printf ("\n-----------------testbuf %d--------------\n", i);
		std::string q_node_sl = genSLStr(3);
		printf ("q_node_sl = %s\n", q_node_sl.c_str());
		std::string node_addr = pub_CreateQNode(q_node_sl);
		pub_AddNodeToQ(&qgrp, qgrp.m_pub_qgroup[0], node_addr);
	}
	
}