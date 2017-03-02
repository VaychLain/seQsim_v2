#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <uuid/uuid.h>
#include <string.h>
#include <string>

#include "qnode.h"
#include "q.h"
#include "qgroup.h"
#include "helps.h"
#include "sl.h"
#include "rslt.h"
#include "tfr.h"

//const char gSL[2][128]={"HIGH","NORMAL"};   //global array storing security level


bool tfrScheduAlg01(PQ_GROUP qgrp_obj, std::string q_node_sl){
	
	std::vector<std::string>::iterator it_str;
	
	pub_CreateQNode(qgrp_obj, q_node_sl);
	
	std::vector<std::string> q_list = pub_GetQueueList(qgrp_obj);
	printf ("q_list.size() = %d\n", q_list);
	for (it_str = q_list.begin(); it_str != q_list.end(); it_str ++) {
		
		int size = pub_GetQSizeByShadowAddr(qgrp_obj, (*it_str).c_str());
		
		if (size == 0){
			int idle = pub_GetQIdleByShadowAddr(qgrp_obj, (*it_str).c_str());
			printf ("idle = %d\n", idle);
			
			if (idle == MAX_IDLE){
				//delete the queue
				
				
			}else{
				pub_UpdateQIdleByShadowAddr(qgrp_obj, (*it_str).c_str());
			}
			
			
		}
	}
		
	return true;
}

int main(int argc, char **argv)
{
	int i;
    std::vector<PQ>::iterator it;
	std::vector<std::string>::iterator it_str;
	Q_GROUP qgrp_obj;
	
	/*for (i = 0; i < 2; i++) {
		if(i == 0)
			pub_CreateQ(&qgrp_obj, gSL[0]);
			pub_CreateQ(&qgrp_obj, "ff,ff,ff")
		else
			pub_CreateQ(&qgrp_obj, gSL[1]);
	}*/
	
	//output the two queues' information
	/*std::vector<std::string> q_list = pub_GetQueueList(&qgrp_obj);	//get queue group with shadow address
	for (it_str = q_list.begin(); it_str != q_list.end(); it_str ++) {
		pub_PrintQueueInfo(&qgrp_obj, (*it_str));
	}*/
	
	// create 10 nodes with random security level, and add these nodes to appropriate queues
//	int node_sl_index = 0;
//	srand(time(NULL));
//	for (i = 0; i < 20; i++) {
////		node_sl_index = rand() % 2;	// only two types of security levels
////		std::string node_addr = pub_CreateQNode(&qgrp_obj, std::string(gSL[node_sl_index]));
//		printf ("\n-----------------add node %d--------------\n", i);
//		std::string q_node_sl = genSLStr(3);
//		printf ("q_node_sl = %s\n", q_node_sl.c_str());
//		std::string node_addr = pub_CreateQNode(&qgrp_obj, q_node_sl);
//	}
/*	srand(time(NULL));
	for (int i=0; i<20; i++){
		printf ("\n-----------------testTfrScheduAlg %d--------------\n", i);
		std::string q_node_sl = genSLStr(3);
		printf ("q_node_sl = %s\n", q_node_sl.c_str());
		tfrScheduAlg01(&qgrp_obj, q_node_sl);
//		pub_CreateQNode(&qgrp_obj, q_node_sl);
	}	*/

	
	testTfrScheduAlg(&qgrp_obj, 20);
	
	pub_PrintQueueInfo(qgrp_obj);
	
//	pub_PrintQNodeInfo(qgrp_obj);
	
	
	// Dequeue a specified queue
	std::vector<std::string> q_list = pub_GetQueueList(&qgrp_obj);
	
	for (int i=0; i<10; i++){
		unsigned int q_index = rand() % (q_list.size());
		std::string q_addr = q_list[q_index];
		std::string deq_node_val = pub_Dequeue(&qgrp_obj, q_addr);
		printf("Dequeued node info: %s q_index = %d\n", deq_node_val.c_str(), q_index);
		
		
//		int idle = pub_GetQIdleByShadowAddr(&qgrp_obj, (*it_str).c_str());
//		printf ("idle = %d\n", idle);
	}
	
	pub_PrintQueueInfo(qgrp_obj);
	
	testTfrScheduAlg(&qgrp_obj, 20);
	
	pub_PrintQueueInfo(qgrp_obj);
	
	//test pub_DeleteQ
	printf("Being deleted queue address: %s\n", qgrp_obj.m_pub_qgroup[0].c_str());
	pub_DeleteQ(&qgrp_obj, qgrp_obj.m_pub_qgroup[0]);
	printf("Being deleted queue address: %s\n", qgrp_obj.m_pub_qgroup[0].c_str());
	pub_DeleteQ(&qgrp_obj, qgrp_obj.m_pub_qgroup[0]);
	printf("Being deleted queue address: %s\n", qgrp_obj.m_pub_qgroup[0].c_str());
	pub_DeleteQ(&qgrp_obj, qgrp_obj.m_pub_qgroup[0]);
	printf("Deletion complete.\n");
	pub_PrintQueueInfo(qgrp_obj);
	
	//test
//	testSLIsDominated(20);
	
	//test rslt
	//rsltDispatcherTP(qgrp_obj);
	
	//test getTargetQForSL
//	testGetTargetQForSL(5);


	//this must be end
	pub_FreeQGroup(&qgrp_obj);
	
	return 0;
}
