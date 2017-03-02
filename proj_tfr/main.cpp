#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <uuid/uuid.h>
#include <string.h>
#include <string>

#include "../qnode.h"
#include "../q.h"
#include "../qgroup.h"
#include "../helps.h"
#include "../sl.h"
#include "../rslt.h"
#include "../tfr.h"
//#include "../globals.h"
#include "tfrnet.h"

int main(int argc, char **argv)
{
	initTfrNet();
	
	return 0;
}




/*
int main(int argc, char **argv)
{

	Q_GROUP qgrp_obj;
	
#if defined(SEC_HIGH)	
	testTfrScheduAlg(&qgrp_obj, 20);
	
	pub_PrintQueueInfo(qgrp_obj);
	
	std::vector<std::string> q_list = pub_GetQueueList(&qgrp_obj);
	
	for (int i=0; i<10; i++){
		unsigned int q_index = rand() % (q_list.size());
		std::string q_addr = q_list[q_index];
		std::string deq_node_val = pub_Dequeue(&qgrp_obj, q_addr);
		printf("Dequeued node info: %s q_index = %d\n", deq_node_val.c_str(), q_index);
	}
	
	pub_PrintQueueInfo(qgrp_obj);
	
	testTfrScheduAlg(&qgrp_obj, 30);
	
	pub_PrintQueueInfo(qgrp_obj);
	
//	pub_FreeQGroup(&qgrp_obj);

	
#elif defined(SEC_LOW)	
	testSecLowTfrScheduAlg(&qgrp_obj, 20);
	
	printf ("queue size = %d\n", qgrp_obj.m_qgroup.size());
	for (int i=0; i<qgrp_obj.m_qgroup.size(); i++){
//		unsigned int q_index = rand() % (q_list.size());
		printf ("\nq index = %d\nm_id = %s\nm_sl = %s\nsize = %d\nidle = %d\n", 
			i, qgrp_obj.m_qgroup[i]->m_id, qgrp_obj.m_qgroup[i]->m_sl, 
			qgrp_obj.m_qgroup[i]->m_queue->size(), qgrp_obj.m_qgroup[i]->idle);
	}
	
	for (int i=0; i<10; i++){
		printf ("i = %d\n", i);
		unsigned int q_index = rand() % (qgrp_obj.m_qgroup.size());
		printf ("q_index = %d\n", q_index);
		std::string deq_node_val = nonSec_Dequeue(qgrp_obj.m_qgroup[q_index]);
		printf("Dequeued node info: %s q_index = %d\n", deq_node_val.c_str(), q_index);
	}
	
	
	testSecLowTfrScheduAlg(&qgrp_obj, 30);
	
	printf ("queue size = %d\n", qgrp_obj.m_qgroup.size());
	for (int i=0; i<qgrp_obj.m_qgroup.size(); i++){
		printf ("\nq index = %d\nm_id = %s\nm_sl = %s\nsize = %d\nidle = %d\n", 
			i, qgrp_obj.m_qgroup[i]->m_id, qgrp_obj.m_qgroup[i]->m_sl, 
			qgrp_obj.m_qgroup[i]->m_queue->size(), qgrp_obj.m_qgroup[i]->idle);
	}
	
//	pub_FreeQGroup(&qgrp_obj);
	
	
	
#elif defined(SEC_NON)
	testSecNonTfrScheduAlg(&qgrp_obj, 20);
	
	printf ("queue size = %d\n", qgrp_obj.m_qgroup.size());
	for (int i=0; i<qgrp_obj.m_qgroup.size(); i++){
		printf ("\nq index = %d\nm_id = %s\nm_sl = %s\nsize = %d\nidle = %d\n", 
			i, qgrp_obj.m_qgroup[i]->m_id, qgrp_obj.m_qgroup[i]->m_sl, 
			qgrp_obj.m_qgroup[i]->m_queue->size(), qgrp_obj.m_qgroup[i]->idle);
	}
	
	for (int i=0; i<10; i++){
		std::string deq_node_val = nonSec_Dequeue(qgrp_obj.m_qgroup[0]);
		printf("Dequeued node info: %s\n", deq_node_val.c_str());
	}
	
	
	testSecNonTfrScheduAlg(&qgrp_obj, 30);
	
	printf ("queue size = %d\n", qgrp_obj.m_qgroup.size());
	for (int i=0; i<10; i++){
		std::string deq_node_val = nonSec_Dequeue(qgrp_obj.m_qgroup[0]);
		printf("Dequeued node info: %s\n", deq_node_val.c_str());
	}
//	pub_FreeQGroup(&qgrp_obj);
	
#endif
	
	return 0;
}
*/