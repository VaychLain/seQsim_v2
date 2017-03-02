#include "../globals.h"
#include "rsltnet.h"
#include "../tfr.h"

#include  <netinet/in.h>
#include <netinet/tcp.h>
#include <glib.h>

GTimer * timer;
int count_push = 0, count_pop = 0;

pthread_t thread[2];
pthread_mutex_t mut;

int qNum;
pthread_cond_t count_threshold_cv; 
pthread_mutex_t mutexTNUM;
int tNum = NUM_THREADS;
std::vector<std::string> q_list;
pthread_t threads[NUM_THREADS];

Q_GROUP qgrp_obj;

void *rec_data(void *fd)  
{  
	int client_sockfd;  
	int n;
	char buff[2048];

	printf("main thread tid = %u\n", pthread_self());
	client_sockfd=*((int*)fd);  
	while(1)
	{
		n = recv(client_sockfd, buff, 1, 0);
		int bufsize = (int)buff[0];
		memset(&buff,0,sizeof(buff));
		n = recv(client_sockfd, buff, bufsize, 0);
		buff[n] = '\0';
		printf("\nrecv msg from client: %s with sock_fd = %d\n", buff, client_sockfd);
		
		std::string q_node_sl = buff;
		
		printf ("q_node_sl = %s\n", q_node_sl.c_str());
		
		pthread_mutex_lock(&mut);
		
		count_push++;
		if (count_push==1){
			g_timer_start(timer);
		}
		 
#if defined(SEC_HIGH)	
		tfrScheduAlg(&qgrp_obj, q_node_sl);
		
#elif defined(SEC_LOW)			
		sec_low_tfrScheduAlg(&qgrp_obj, q_node_sl);
		
#elif defined(SEC_NON)		
		sec_non_tfrScheduAlg(&qgrp_obj, q_node_sl);

#endif		
		pthread_mutex_unlock(&mut);
		
//		close(client_sockfd);  
//		pthread_exit(0);
	}
	
	close(client_sockfd);  
}  


void * send_data(void * sock_fd){
	
	int i = 0;

	while (true){
		
		std::string deq_node_val("");
		pthread_mutex_lock(&mut);
		
		q_list = pub_GetQueueList(&qgrp_obj);
		if (q_list.size() == 0 && qgrp_obj.m_qgroup.size() == 0){
			pthread_mutex_unlock(&mut);
			continue;
		}
//		qNum = q_list.size();
		qNum = qgrp_obj.m_qgroup.size();
				
		pthread_mutex_lock(&mutexTNUM);
		if (tNum > qNum){		//busyThreads is too many, to block
			printf ("\npthread_cond_wait: tNum = %d qNum = %d\n", tNum, qNum);
			tNum--;
			
			pthread_mutex_unlock(&mut);
			
			pthread_cond_wait(&count_threshold_cv, &mutexTNUM); 
			printf ("I wake up\n");
			pthread_mutex_unlock(&mutexTNUM);
			continue;
		}else if(tNum < qNum && tNum < NUM_THREADS){
			printf ("\npthread_cond_signal: tNum = %d qNum = %d\n", tNum, qNum);
			pthread_cond_signal(&count_threshold_cv); 
			tNum++;
		}
		pthread_mutex_unlock(&mutexTNUM);
				
#if defined(SEC_HIGH)		
		i++;
		i = i % q_list.size();
		std::string q_addr = q_list[i];
		
		/*int a = pthread_mutex_trylock (&(qgrp_obj.m_qgroup[i]->mutex));
		if (a != 0){
			//there must unlock, or the writeThread can't proceed

			pthread_mutex_unlock(&mut);
			continue;
		}*/
		int size = pub_GetQSizeByShadowAddr(&qgrp_obj, q_addr.c_str());
		if (size == 0){
//			pthread_mutex_unlock (&(qgrp_obj.m_qgroup[i]->mutex)); 
			
			pthread_mutex_unlock(&mut);
			continue;
		}
		
		deq_node_val = pub_Dequeue(&qgrp_obj, q_addr);
		printf("Dequeued node info %s frome queue %d by thread %u\n", deq_node_val.c_str(), i, pthread_self());
		
//		pthread_mutex_unlock (&(qgrp_obj.m_qgroup[i]->mutex)); 

#elif defined(SEC_LOW)
		i++;
		i = i % qgrp_obj.m_qgroup.size();
//		printf ("i = %d\n", i);
		
//		printf ("q_index = %d\n", i);
		
		int size = qgrp_obj.m_qgroup[i]->m_queue->size();
		if (size == 0){			
			pthread_mutex_unlock(&mut);
			continue;
		}
		
		deq_node_val = nonSec_Dequeue(qgrp_obj.m_qgroup[i]);
		printf("Dequeued node info: %s q_index = %d\n", deq_node_val.c_str(), i);
		

#elif defined(SEC_NON)
		
		int size = qgrp_obj.m_qgroup[0]->m_queue->size();
		if (size == 0){			
			pthread_mutex_unlock(&mut);
			continue;
		}
		
		deq_node_val = nonSec_Dequeue(qgrp_obj.m_qgroup[0]);
		printf("Dequeued node info: %s q_index = %d\n", deq_node_val.c_str(), 0);

#endif
		
		gulong* se;
		gdouble elapsed_time;
		count_pop++;
		timeToFile("pop.txt",count_pop);
		if (count_pop==TEST_CASE_NUM)
		{
			
			g_timer_stop (timer);
			elapsed_time = g_timer_elapsed (timer,se);
			printf("time elapsed: %lf\n", elapsed_time);
			timeToFile("rslt.txt", elapsed_time);
			count_pop = 0;
			count_push = 0;
		} 
		
		printf("droped data: %s\n",deq_node_val.c_str());
		
//		int sockid = (long)sock_fd;
//		
//		int len = deq_node_val.size();
//		if(send(sockid, &len, 4, 0) < 0)
//		{
//			perror("send msg error");
//			exit(0);
//		}	
//		if(send(sockid, deq_node_val.c_str(), deq_node_val.size(), 0) < 0)
//		{
//			perror("send msg error");
//			exit(0);
//		}	
//		printf ("send %s completed by thread %u with sock_fd = %d\n", deq_node_val.c_str(), pthread_self(), sock_fd);
//		
		
		pthread_mutex_unlock(&mut);
		
		/*int len = deq_node_val.size();
		if(send(sock_fd, &len, 4, 0) < 0)
		{
			perror("send msg error");
			exit(0);
		}	*/
		
//		sleep(1);
		
//		close(sock_fd);
//		break;
	}	
	
//	close(sock_fd);
	
//	pthread_exit(NULL); 
}


void *listenThread(void *ptr)
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

	printf("listen\n");
	while(1)  
	{  
		
		connfd  = accept(listen_sock, (struct sockaddr *)&clientaddr,  (socklen_t *)&socklen);  
		if(connfd  < 0)  
		{
			perror("accept failed");  
			exit(1);  
		}
		printf ("new client accept...\n");
		
		if(pthread_create(&thread[0], NULL, rec_data, &connfd) != 0){
			perror("pthread_create");  
			continue;  
		}          
	}
}




void *popThread(void *ptr)
{
	int sock_fd = 0;
	char sendline[2048]="hello.";
	struct sockaddr_in ser_addr;
	std::string stemp;
	
	memset(&sendline, 0, sizeof(sendline)); 
//	
//	memset(&ser_addr, 0, sizeof(ser_addr));  
//	ser_addr.sin_family = AF_INET;  
//	inet_aton("127.0.0.1", (struct in_addr *)&ser_addr.sin_addr);  
//	ser_addr.sin_port = htons(SERVER_PORT);  
//	sock_fd = socket(AF_INET, SOCK_STREAM, 0);  
//		
//	if(sock_fd < 0)  
//	{  
//		perror("create socket failed") ; 
//		exit(1);  
//	}  
//	
//	if(connect(sock_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)  
//	{  
//		perror("connect socket failed");  
//		exit(1);  
//	}  
//	
//	pthread_attr_t attr; 
//	pthread_attr_init(&attr);
//	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); 
	for (int i=0; i<NUM_THREADS; i++){
		printf ("create thread %d\n", i);
						
		int rc = pthread_create(&threads[i], NULL, send_data, NULL); 
		if (rc){
			 printf("ERROR; return code from pthread_create() is %d\n", rc); 
		}
	}
	
	for (int i=0; i<NUM_THREADS; i++){
		pthread_join(threads[i], NULL); 
	}
	
	
	close(sock_fd);
}



void thread_create(void)
{
	int temp;
	memset(&thread, 0, sizeof(thread));    
	
//	pthread_t threads[NUM_THREADS], tfrThread;
	
	pthread_attr_t attr; 
	
	pthread_cond_init (&count_threshold_cv, NULL); 
	pthread_mutex_init(&mutexTNUM, NULL);
//	pthread_mutex_init(&mutex_1, NULL);
//	pthread_mutex_init(&mutex_2, NULL);
//	pthread_rwlock_init(&rwlock, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); 
	
	
	if((temp = pthread_create(&thread[1], NULL, listenThread, NULL)) != 0)  
		printf("create listenThread faild",temp);
	else
		printf("listenThread created\n");
	
	sleep(1);
	
	/*create thread*/
	if((temp = pthread_create(&thread[0], NULL, popThread, NULL)) != 0)       
		printf("create popThread faild!\n");
	else
		printf("popThread created,%d\n",temp);
	
	/*for (int i=0; i<NUM_THREADS; i++){
		printf ("create thread %d\n", i);
						
		int rc = pthread_create(&threads[i], NULL, popThread, (void *)i); 
		if (rc){
			 printf("ERROR; return code from pthread_create() is %d\n", rc); 
		}
	}*/
}


void thread_wait(void)
{
	/*wait for thread1,2 exit*/
	if(thread[0] !=0) {                   
		pthread_join(thread[0],NULL);
		printf("popThread exit\n");
	}
	if(thread[1] !=0) {                
		pthread_join(thread[1],NULL);
		printf("listenThread exit\n");
	}
	/*for (int i=0; i<NUM_THREADS; i++){
		pthread_join(threads[i], NULL); 
	}*/
}


void initRsltNet(){
	
	pthread_mutex_init(&mut,NULL);
	
/*#if defined(SEC_HIGH)	
	testTfrScheduAlg(&qgrp_obj, 20);
	
#elif defined(SEC_LOW)	
	testSecLowTfrScheduAlg(&qgrp_obj, 20);
	
#elif defined(SEC_NON)
	testSecNonTfrScheduAlg(&qgrp_obj, 20);

#endif*/
	
	timer = g_timer_new();
	
	thread_create();
	thread_wait();
	
	pthread_mutex_destroy(&mut);
}