#ifndef TFR_H
#define TFR_H

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

#include <stdio.h>
#include <iostream>
#include <queue>

#include <syslog.h>  
#include <errno.h>  

#include <glib.h>  

#include "../qnode.h"
#include "../q.h"
#include "../qgroup.h"
#include "../sl.h"

#define SERVER_PORT 10003
#define MAX 5

#define MAX_LISTEN_NUM 5  
#define SEND_BUF_SIZE 128  
#define RECV_BUF_SIZE 128  
#define LISTEN_PORT 10002


extern pthread_t thread[2];
extern pthread_mutex_t mut;


extern std::queue<std::string> queue1;

extern Q_GROUP qgrp;
extern GTimer * timer;
extern int count_push,count_pop;
/**
 * @brief enqueue thread
 * @param ptr
 */
void *pushThread(void *ptr);
/**
 * @brief dequeue thread
 * @param ptr
 */
void *popThread(void *ptr);
/**
 * @brief create threads
 */
void thread_create(void);
/**
 * @brief wait for threads quit
 */
void thread_wait(void);

/**
 * @brief using for test
 * @param q_grp
 * @param n
 */
void testbuf(PQ_GROUP q_grp, int n);

#endif