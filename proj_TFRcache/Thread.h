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

#define SERVER_PORT 10001

extern pthread_t thread[2];
extern pthread_mutex_t mut1;
extern pthread_mutex_t mut2;
extern pthread_mutex_t* mut_arr[2];

extern std::queue<std::string> queue1;
extern std::queue<std::string> queue2;
extern std::vector<std::queue<std::string> > queue;
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

#endif