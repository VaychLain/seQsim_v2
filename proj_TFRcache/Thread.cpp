//#define SECURED_STRONG
//#define SECURED_NORMAL
//#define NON_SECURED

#include "Thread.h"
#include "../helps.h"
#include "../globals.h"

void *pushThread(void *ptr)
{
	int i=1;
	int idx;
	char c;
	
	FILE * fp;
//	std::strint head;
	std::string filename("../../sldata/sl_");
	
	std::string tail(".txt");
	
	
	std::string pushdate;
	char buf[128];
	while(c = getchar()){
//		filename += c;
//		filename.append(tail);
		std::cout <<"Open file"<<filename+c+tail<<std::endl;
		
		if ((fp = fopen((filename+c+tail).c_str(), "rb")) == NULL){
		printf ("error!");
	}
		

	while (!feof(fp)){
		idx=i%2;
		i++;
		if(pthread_mutex_trylock(mut_arr[idx])==0)
		{
			fscanf(fp, "%s\n", buf);
			pushdate = buf;
			std::cout <<"Enqueue " << idx+1<<": "<< pushdate<<std::endl;
			
			count_push++;
			if (count_push==1){
				g_timer_start(timer);
			}
			
#ifdef SEC_HIGH
			std::string node_addr = pub_CreateQNode(pushdate);
			pub_AddNodeToQ(&qgrp, qgrp.m_pub_qgroup[idx], node_addr);
#else
			queue[idx].push(pushdate);
#endif
			pthread_mutex_unlock(mut_arr[idx]);
		//	sleep(1);
		}
		else 
			std::cout << "Can't lock queue"<<idx+1<<std::endl;
	}
	std::cout << "push ended"<<std::endl;
	fclose(fp);
	getchar();
	}
    	
	
	return 0;
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
	inet_aton("172.17.0.3", (struct in_addr *)&ser_addr.sin_addr);  
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
#ifdef SEC_HIGH
			while (pub_GetQSizeByShadowAddr(&qgrp,qgrp.m_pub_qgroup[i].c_str()))
			{
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
				printf("pop from queue: %d",i);
				std::cout << ' ' << sendline << std::endl;
				bufsize = (char)strlen(sendline);
				
				//timer module
				count_pop++;
				if (count_pop==TEST_CASE_NUM)
				{
					g_timer_stop (timer);
					elapsed_time = g_timer_elapsed (timer,se);
					printf("time elapsed: %lf\n", elapsed_time);
					timeToFile("tfrcache.txt", elapsed_time);
					count_pop = 0;
					count_push = 0;
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
//		else if(pthread_mutex_trylock(&mut2)==0)
//		{
////		printf("search queue2: ");
//				
//#ifdef SECURED_STRONG
//			while (pub_GetQSizeByShadowAddr(&qgrp,qgrp.m_pub_qgroup[1].c_str()))
//			{
//				stemp = pub_Dequeue(&qgrp, qgrp.m_pub_qgroup[1]);
////				strcpy(sendline,stemp.c_str());
//				split_string(stemp, splitted_str, "|");
//				strcpy(sendline,splitted_str[1].c_str());
//				std::vector<std::string>().swap(splitted_str);
//				//printf("%s\n\n\n",sendline);
//#else
//			while (!queue2.empty())
//			{
//				strcpy(sendline,queue2.front().c_str());
//				queue2.pop();
//#endif
//				printf("pop from queue2: ");
//				std::cout << ' ' << sendline << std::endl;
//				if(send(sock_fd,sendline, strlen(sendline), 0) < 0)
//				{
//					perror("send msg error");
//					exit(0);
//				}
//				memset(&sendline,0,sizeof(sendline));
//			}
//			pthread_mutex_unlock(&mut2);
//		} 
		else 
		{
			printf("Empty queue\n");
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
	sleep(1);
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