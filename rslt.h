#ifndef RSLT_H
#define RSLT_H

#include <string>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "qgroup.h"
#include "tfr.h"

#define MAX_IDLE	20

void * dispatcher();
void rsltDispatcher(Q_GROUP qgrp_obj);

void * dispatcherTP();
void rsltDispatcherTP(Q_GROUP qgrp_obj);


void * tfrTest();
	
	
#endif