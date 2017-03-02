#include "RSLTcache.h"
#include "../qnode.h"
#include "../q.h"
#include "../qgroup.h"
//#include "../sl.h"
#include <iostream>

pthread_t thread[2];

pthread_mutex_t mut1;
pthread_mutex_t mut2;
pthread_mutex_t* mut_arr[2];

std::queue<std::string> queue1;
std::queue<std::string> queue2;
std::vector<std::queue<std::string> > queue;

Q_GROUP qgrp;
GTimer * timer;
int count_push,count_pop;

int main()  
{
	count_push = 0;
	count_pop = 0;
	mut_arr[0]=&mut1;
	mut_arr[1]=&mut2;
	queue.push_back(queue1);
	queue.push_back(queue2);
	
	int i;
	std::string data1 ="111|ff,ff,ff";
	std::string data2 ="222|ff,ff,ff";
	
	timer = g_timer_new ();
	for (i = 0; i < 2; i++) {
		pub_CreateQ(&qgrp, "ff,ff,ff");
	}
	
	pthread_mutex_init(&mut1,NULL);
	pthread_mutex_init(&mut2,NULL);

	//testbuf(&qgrp, 100);

	printf("createing threads\n");
	thread_create();	
	thread_wait();
	

}  