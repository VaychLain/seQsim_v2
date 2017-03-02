#include <string.h>
#include "rslt.h"
#include "qgroup.h"

#ifndef NUM_THREADS
#define NUM_THREADS     20
#endif

Q_GROUP qgrp_obj;
pthread_mutex_t mutex[NUM_THREADS];


void * dispatcher(void * tid){
	// find a specified queue
	std::vector<std::string> q_list = pub_GetQueueList(&qgrp_obj);
	int i=0; 
	
	while (true){
		i++;
		i = i % q_list.size();
				
		//operate one of the q_list
		int a = pthread_mutex_trylock (&mutex[i]);
		//printf ("a = %d\n", a);
		if (a != 0){
			continue;
		}
		
		// Dequeue a specified queue
		std::string q_addr = q_list[i];
		std::string deq_node_val = pub_Dequeue(&qgrp_obj, q_addr);
		printf("Dequeued node info %s frome queue %d by thread %d\n", deq_node_val.c_str(), i, tid);
		
		printf ("the queque %d has been locked by thread %d\n", i, tid);
		sleep(10);
		
		pthread_mutex_unlock (&mutex[i]); 
		printf ("the queque %d has been unlocked by thread %d\n", i, tid);
		
		sleep(5);
	}
	
	pthread_exit(NULL); 
}



void rsltDispatcher(Q_GROUP qgrp){
	int rc;
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr; 
	
	//init qgrp_obj, in fact, the variable qgrp_obj should be shared
	qgrp_obj = qgrp;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); 
	
	for (int i=0; i<NUM_THREADS; i++){
		printf ("create thread %d\n", i);
		
		pthread_mutex_init(&mutex[i], NULL);
		
		
		rc = pthread_create(&threads[i], NULL, dispatcher, (void *)i); 
		if (rc){ 
			 printf("ERROR; return code from pthread_create() is %d\n", rc); 
		}
		
	}
	
	for (int i=0; i<NUM_THREADS; i++){
		pthread_join(threads[i], NULL); 
	}
	
	//free resource
	for (int i=0; i<NUM_THREADS; i++){
		pthread_mutex_destroy(&mutex[i]);
	}
	pthread_exit(NULL); 
}




pthread_cond_t count_threshold_cv; 
pthread_mutex_t mutexTNUM;
int tNum = NUM_THREADS;

//pthread_rwlock_t mutexRW;	//, mutexQNUMRW;
//pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_t rwlock;
bool isTfr = false;
pthread_mutex_t		mutex_1;
pthread_mutex_t		mutex_2;

void * dispatcherTP(void * tid){
	
	int i = 0;
	std::vector<std::string> q_list;
	int qNum;
	
	while (true){
		
		if (isTfr){
			continue;
		}
		
		pthread_rwlock_rdlock(&rwlock);
		////////////LD///////////
		////////////SUN///////////pthread_mutex_lock(&mutex_1);
		
		q_list = pub_GetQueueList(&qgrp_obj);
		if (q_list.size() == 0){
			//one thread keep alive eventually
			pthread_rwlock_unlock(&rwlock);
			////////////LD///////////
			////////////SUN///////////pthread_mutex_unlock(&mutex_1);
			continue;
		}
		i++;
		i = i % q_list.size();
		qNum = q_list.size();
		std::string q_addr = q_list[i];

		pthread_mutex_lock(&mutexTNUM);
		if (tNum > qNum){		//busyThreads is too many, to block
			printf ("\npthread_cond_wait: tNum = %d qNum = %d\n", tNum, qNum);
			tNum--;
			//unlock rw
			pthread_rwlock_unlock(&rwlock);
			////////////LD///////////
			////////////SUN///////////pthread_mutex_unlock(&mutex_1);
			
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
		
		
//		int a = pthread_mutex_trylock (&mutex[i]);
		int a = pthread_mutex_trylock (&(qgrp_obj.m_qgroup[i]->mutex));
		if (a != 0){
			//there must unlock, or the writeThread can't proceed
			pthread_rwlock_unlock(&rwlock);
			////////////LD///////////
			///////////SUN/////////pthread_mutex_unlock(&mutex_1);
			continue;
		}
		
		int size = pub_GetQSizeByShadowAddr(&qgrp_obj, q_addr.c_str());
		if (size == 0){
//			pthread_mutex_unlock (&mutex[i]); 
			pthread_mutex_unlock (&(qgrp_obj.m_qgroup[i]->mutex)); 
			
			pthread_rwlock_unlock(&rwlock);
			////////////LD///////////
			////////////SUN///////////pthread_mutex_unlock(&mutex_1);
			continue;
		}
		
		std::string deq_node_val = pub_Dequeue(&qgrp_obj, q_addr);
		printf("Dequeued node info %s frome queue %d by thread %d\n", deq_node_val.c_str(), i, tid);
		
//		pthread_mutex_unlock (&mutex[i]); 
		pthread_mutex_unlock (&(qgrp_obj.m_qgroup[i]->mutex)); 
		
		pthread_rwlock_unlock(&rwlock);
		////////////LD//////////
		////////SUN////////pthread_mutex_unlock(&mutex_1);
	}	
	
	pthread_exit(NULL); 
}

void * tfrScheduAlgThread(void * tid){
	
	//for (int i=0; i<1; i++){
	while (true){
		//sleep(5);
		printf ("\n---------------------------tfrScheduAlgThread------------------\n");
	
		//std::string q_node_sl = genSLStr(3);
//		std::string q_node_sl("00,ff,v0");// = genSLStr(3);
		char qnode_sl_buf[10] = {0};
		genSLCStr(3, qnode_sl_buf);
		std::string q_node_sl(qnode_sl_buf);
		
		printf ("q_node_sl = %s\n", qnode_sl_buf);
		if (strcmp("ff,ff,ff", qnode_sl_buf) == 0){
			printf ("********q_node_sl == ff,ff,ff\n**************");
			continue;
		}
		
		isTfr = true;
		
		pthread_rwlock_wrlock(&rwlock);
		////////////LD///////////
//		pthread_mutex_lock(&mutex_1);
		
		tfrScheduAlg(&qgrp_obj, q_node_sl);
		
		pthread_rwlock_unlock(&rwlock);
		////////////LD///////////
//		pthread_mutex_unlock(&mutex_1);
				
		isTfr = false;
	}
	
	pthread_exit(NULL); 
}


void rsltDispatcherTP(Q_GROUP qgrp){
	pthread_t threads[NUM_THREADS], tfrThread;
	
	//init qgrp_obj, in fact, the variable qgrp_obj should be shared
	qgrp_obj = qgrp;
	
	pthread_attr_t attr; 
	
	pthread_cond_init (&count_threshold_cv, NULL); 
	pthread_mutex_init(&mutexTNUM, NULL);
	pthread_mutex_init(&mutex_1, NULL);
	pthread_mutex_init(&mutex_2, NULL);
	pthread_rwlock_init(&rwlock, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); 
	
	for (int i=0; i<NUM_THREADS; i++){
		printf ("create thread %d\n", i);
						
		int rc = pthread_create(&threads[i], NULL, dispatcherTP, (void *)i); 
		if (rc){
			 printf("ERROR; return code from pthread_create() is %d\n", rc); 
		}
	}
	
	pthread_create(&tfrThread, NULL, tfrScheduAlgThread, (void *)NULL); 
	
	for (int i=0; i<NUM_THREADS; i++){
		pthread_join(threads[i], NULL); 
	}
	pthread_join(tfrThread, NULL); 
	
	pthread_attr_destroy(&attr); 
	pthread_cond_destroy(&count_threshold_cv);
	pthread_rwlock_destroy(&rwlock);
	pthread_mutex_destroy(&mutexTNUM);
	
	pthread_exit(NULL);
}
