#include "bufThre.h"
#include "../qnode.h"
#include "../q.h"
#include "../qgroup.h"

#include <iostream>

pthread_t thread[2];
pthread_mutex_t mut;

std::queue<std::string> queue1;

Q_GROUP qgrp;
GTimer * timer;
int count_push,count_pop;


int main()  
{
	count_push = 0;
	count_pop = 0;
	pub_CreateQ(&qgrp, "ff,ff,ff");
	pthread_mutex_init(&mut,NULL);
	timer = g_timer_new ();
	//testbuf(&qgrp, 100);

	printf("createing threads\n");
	thread_create();
	thread_wait();
}  