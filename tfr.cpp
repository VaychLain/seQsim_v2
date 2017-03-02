#include "tfr.h"
#include "sl.h"
#include "qnode.h"
#include "q.h"
#include "qgroup.h"


bool tfrScheduAlg(PQ_GROUP q_grp, std::string q_node_sl){
	
//	std::vector<std::string>::iterator it_str;
	
	pub_CreateQNode(q_grp, q_node_sl);
	
	std::vector<std::string> q_list = pub_GetQueueList(q_grp);
	printf ("q_list.size() = %d\n", q_list.size());
	
//	for (it_str = q_list.begin(); it_str != q_list.end(); it_str ++) {
	for (int i=0; i<q_list.size(); i++){
		
		int size = pub_GetQSizeByShadowAddr(q_grp, q_list[i].c_str());
		
		if (size == 0){
			int idle = pub_GetQIdleByShadowAddr(q_grp, q_list[i].c_str());
			printf ("queue index = %d idle = %d\n", i, idle);
			
			if (idle >= MAX_IDLE){
				//delete the queue
				pub_DeleteQ(q_grp, q_list[i].c_str());
				printf ("deleteQ completed\n");
				
			}else{
				pub_UpdateQIdleByShadowAddr(q_grp, q_list[i].c_str());
			}
			
			
		}
	}
		
	return true;
}


bool sec_low_tfrScheduAlg(PQ_GROUP q_grp, std::string sl){
		
	PQ_NODE qNode = nonSec_CreateQNode(sl);
	
	PQ q = find_queue_by_sl(sl, q_grp);
	if (q == NULL){
		printf ("q == NULL\n");
		q = nonSec_CreateQ(sl);
		nonSec_AddQToQGroup(q_grp, q);
	}
	nonSec_Enqueue(q, qNode);
	printf ("q_list.size() = %d\n", q_grp->m_qgroup.size());
	
	for (int i=0; i<q_grp->m_qgroup.size(); i++){
		int size = q_grp->m_qgroup[i]->m_queue->size();
		
		if (size == 0){
			int idle = q_grp->m_qgroup[i]->idle;
			printf ("queue index = %d idle = %d\n", i, idle);
			if (idle >= MAX_IDLE){
				nonSec_DeleteQ(q_grp, q_grp->m_qgroup[i]->m_id);
				printf ("deleteQ completed\n");
			}else {
				q_grp->m_qgroup[i]->idle++;
			}
		}
	}
	
	return true;
}

bool sec_non_tfrScheduAlg(PQ_GROUP q_grp, std::string sl){
		
	PQ_NODE qNode = nonSec_CreateQNode(sl);
	
//	PQ q = q_grp->m_qgroup[0]
	if (q_grp->m_qgroup.size() == 0){
		PQ q = nonSec_CreateQ("ff,ff,ff");
		nonSec_AddQToQGroup(q_grp, q);
	}
	nonSec_Enqueue(q_grp->m_qgroup[0], qNode);
	
	printf ("q_list.size() = %d\n", q_grp->m_qgroup.size());
	
	return true;
}


void testTfrScheduAlg(PQ_GROUP q_grp, int n){
		
	for (int i=0; i<n; i++){
		printf ("\n-----------------testTfrScheduAlg %d--------------\n", i);
		std::string q_node_sl = genSLStr(3);
		printf ("q_node_sl = %s\n", q_node_sl.c_str());
		tfrScheduAlg(q_grp, q_node_sl);
	}
	
}

void testSecLowTfrScheduAlg(PQ_GROUP q_grp, int n){
	for (int i=0; i<n; i++){
		printf ("\n-----------------testSecLowTfrScheduAlg %d--------------\n", i);
		std::string q_node_sl = genSLStr(3);
		printf ("q_node_sl = %s\n", q_node_sl.c_str());
		sec_low_tfrScheduAlg(q_grp, q_node_sl);
	}
}

void testSecNonTfrScheduAlg(PQ_GROUP q_grp, int n){
	for (int i=0; i<n; i++){
		printf ("\n-----------------testSecLowTfrScheduAlg %d--------------\n", i);
		std::string q_node_sl = genSLStr(3);
		printf ("q_node_sl = %s\n", q_node_sl.c_str());
		sec_non_tfrScheduAlg(q_grp, q_node_sl);
	}
}