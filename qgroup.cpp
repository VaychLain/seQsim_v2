#include <vector>
#include <queue>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "helps.h"
#include "qnode.h"
#include "q.h"
#include "qgroup.h"
#include "SecretKeeper.h"

class erase_q_from_qvector;

PQ find_queue_by_shadow_addr(PQ_GROUP q_grp, const char* shd_addr) {
	PQ ret_q = NULL;
	std::vector<Q_MAP>::iterator it_q_map;
	
	if (q_grp == NULL || shd_addr == NULL) {
		return ret_q;
	}
	
	std::string shd_addr_string(shd_addr);
	
	//find matched item in queue map vector
	for (it_q_map = q_grp->m_qmap.begin(); it_q_map != q_grp->m_qmap.end(); it_q_map++) {
		if(shd_addr_string.compare((*it_q_map).m_shadow_addr) == 0)
			return ret_q = (*it_q_map).m_queue;
	}

	return ret_q;
}

/**
 * @brief Erase queue from Q_GROUP.m_qgroup, Q_GROUP.m_qmap, Q_GROUP.m_pub_qgroup
 * @param q_grp
 * @param q
 * @return Does function execute successfully?
 */
bool erase_q_from_qvector(PQ_GROUP q_grp, PQ q) {
	bool ret = false;
	
	if(q_grp == NULL || q == NULL)
		return ret;
		
	std::string q_id(q->m_id);	//real id
	std::string q_shd_id(md5_func(q->m_id));	//shadow id
	bool found_target_q = false;
	std::vector<PQ>::iterator q_it;
	std::vector<Q_MAP>::iterator qmap_it;
	std::vector<std::string>::iterator qshd_it;
	
	for(q_it = q_grp->m_qgroup.begin(); q_it != q_grp->m_qgroup.end(); q_it++) {
		if(q_id.compare((*q_it)->m_id) == 0) {
			q_grp->m_qgroup.erase(q_it);
			found_target_q = true;
			break;
		}
	}
	
	if(!found_target_q)
		return ret;
	
	for(qshd_it = q_grp->m_pub_qgroup.begin(); qshd_it != q_grp->m_pub_qgroup.end(); qshd_it++) {
		if((*qshd_it).compare(q_shd_id) == 0) {
			q_grp->m_pub_qgroup.erase(qshd_it);
			break;
		}
	}
	
	for(qmap_it = q_grp->m_qmap.begin(); qmap_it != q_grp->m_qmap.end(); qmap_it++) {
		if(q_shd_id.compare((*qmap_it).m_shadow_addr) == 0) {
			q_grp->m_qmap.erase(qmap_it);
			break;
		}
	}
	
	ret = true;
	
	return ret;
}

PQ find_queue_by_sl(PQ_GROUP q_grp, std::string q_sl) {
	PQ ret_q = NULL;
	std::vector<PQ>::iterator it_q;
	
	if (q_grp == NULL || q_sl.empty()) {
		return ret_q;
	}
	
	for(it_q = q_grp->m_qgroup.begin(); it_q != q_grp->m_qgroup.end(); it_q ++) {
		if(q_sl == std::string((*it_q)->m_sl)) {
			ret_q = (*it_q);
			return ret_q;
		}
	}
	
	return ret_q;
}

PQ_NODE find_node_by_shadow_addr(PQ_GROUP q_grp, std::string node_shd_addr) {
	PQ_NODE q_node = NULL;
	if (q_grp == NULL || node_shd_addr.empty())
		return q_node;
	
	// iterator for Q_GROUP::m_pub_qgroup
	std::vector<std::string>::iterator it_qlist_shd_addr;
	for(it_qlist_shd_addr = q_grp->m_pub_qgroup.begin(); 
		it_qlist_shd_addr != q_grp->m_pub_qgroup.end();
		it_qlist_shd_addr ++) 
	{
		PQ q = find_queue_by_shadow_addr(q_grp, (*it_qlist_shd_addr).c_str());
		if (q != NULL) {
			if ((q_node = find_node_by_shadow_addr(q, node_shd_addr)) != NULL)
				return q_node;
		}
	}// for
	
	return q_node;
}

PQ_NODE find_node_by_shadow_addr(PQ q, std::string node_shd_addr) {
	PQ_NODE q_node = NULL;
	
	if(q == NULL || node_shd_addr.empty())
		return q_node;
	
	std::vector<Q_NODE_MAP>::iterator it_qnode_map;
	for(it_qnode_map = q->m_qnodemap.begin(); it_qnode_map != q->m_qnodemap.end(); it_qnode_map ++) {
		if(node_shd_addr.compare((*it_qnode_map).m_shadow_addr) == 0) {
			return q_node = (*it_qnode_map).m_node;
		}
	}
	
	return q_node;
}

void free_queue_grp(std::vector<PQ> &q_grp) {
    std::vector<PQ>::iterator it;
	PQ del_Q = NULL;

    if (q_grp.size() == 0)  //empty vector
        return;

    for(it=q_grp.begin(); it!=q_grp.end(); it++){
		del_Q = (*it);
        free_queue(del_Q->m_queue);
        delete del_Q;
		del_Q = NULL;
		q_grp.erase(it);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

// Public function: get queue's security level by queue's shadow address
std::string pub_GetQSLByShadowAddr(PQ_GROUP q_grp, const char* shd_addr) {
	std::string sl("");
	PQ q = NULL;
	
	if (q_grp == NULL || shd_addr == NULL) {
		return sl;
	}
	
	q = find_queue_by_shadow_addr(q_grp, shd_addr);
	
	if(q == NULL)
		return sl;
		
	sl = std::string(q->m_sl);
	
	return sl;
}


int pub_GetQIdleByShadowAddr(PQ_GROUP q_grp, const char* shd_addr){
//	std::string sl("");
//	int idle;
	PQ q = NULL;
	
	if (q_grp == NULL || shd_addr == NULL) {
		return -1;
	}
	
	q = find_queue_by_shadow_addr(q_grp, shd_addr);
	
	if(q == NULL)
		return -1;
		
//	sl = std::string(q->m_sl);
	
	return q->idle;
}

bool pub_UpdateQIdleByShadowAddr(PQ_GROUP q_grp, const char* shd_addr){
//	std::string sl("");
//	int idle;
	PQ q = NULL;
	
	if (q_grp == NULL || shd_addr == NULL) {
		return false;
	}
	
	q = find_queue_by_shadow_addr(q_grp, shd_addr);
	
	if(q == NULL)
		return false;
		
//	sl = std::string(q->m_sl);
	q->idle = q->idle + 1;
	
	return true;
}


int pub_GetQSizeByShadowAddr(PQ_GROUP q_grp, const char* shd_addr){
//	std::string sl("");
//	int idle;
	PQ q = NULL;
	
	if (q_grp == NULL || shd_addr == NULL) {
		return -1;
	}
	
	q = find_queue_by_shadow_addr(q_grp, shd_addr);
	
	if(q == NULL)
		return -1;
		
//	sl = std::string(q->m_sl);
	
	return q->m_queue->size();
}

// Public function: get queue from queue group by queue's security level
// Note: this function only returns queue's shadow address
std::string pub_GetQueueFromQgrpBySL(PQ_GROUP q_grp, std::string q_sl) {
	std::string ret_addr("");
	PQ q = NULL;
	std::vector<Q_MAP>::iterator it_q_map;
	
	if (q_grp == NULL || q_sl.empty())
		return ret_addr;
		
	if((q = find_queue_by_sl(q_grp, q_sl)) == NULL)
		return ret_addr;
		
	for(it_q_map = q_grp->m_qmap.begin(); it_q_map != q_grp->m_qmap.end(); it_q_map ++) {
		if ((*it_q_map).m_queue == q) {	//real address matched
			ret_addr = std::string((*it_q_map).m_shadow_addr);
			return ret_addr;
		}
	}
	
	return ret_addr;
}

std::vector<std::string>& pub_GetQueueList(PQ_GROUP q_grp) {
	if(q_grp != NULL)
		return q_grp->m_pub_qgroup;
	
	q_grp = new Q_GROUP;
	return q_grp->m_pub_qgroup;
}

// get queue node map by given queue shadow address
std::vector<Q_NODE_MAP>& pub_GetQNodeMapByShadowAddr(PQ_GROUP q_grp, std::string q_addr) {
	PQ tmp_q = NULL;
	if (q_grp == NULL || q_addr.empty()) {
		tmp_q = new Q;
		return tmp_q->m_qnodemap;
	}
	
	PQ q = find_queue_by_shadow_addr(q_grp, q_addr.c_str());
	if (q == NULL) {
		tmp_q = new Q;
		return tmp_q->m_qnodemap;
	}
	
	return q->m_qnodemap;
} 

//Public function: create a queue and returns a shadow address
std::string pub_CreateQ(PQ_GROUP q_grp, std::string q_sl) {
	std::string ret_addr("");
	PQ q = NULL;
	
	if(q_grp == NULL || q_sl.empty())
		return ret_addr;
	
	// create a new queue and insert it to queue group
	// returns a real address
	q = create_queue(q_grp->m_qgroup, q_sl.c_str());
	if(q == NULL)
		return ret_addr;
	
	// create a corresponding shadow address
	ret_addr = md5_func(q->m_id);
	
	// create a new queue map
	Q_MAP q_map;
	init_qmap(&q_map);
	strcpy(q_map.m_id, q->m_id);
	strcpy(q_map.m_shadow_addr, ret_addr.c_str());
	q_map.m_queue = q;
	q_grp->m_qmap.push_back(q_map);
	
	//save shadow address to "public" queue group
	q_grp->m_pub_qgroup.push_back(ret_addr);
	
	return ret_addr;
}

/**
 * @brief Create a queue node without adding it to a queue group
 * @param q_sl
 * @return The queue shadow address
 */
std::string pub_CreateQ(std::string q_sl) {
	std::string ret_addr("");
	PQ q = NULL;
	
	if(q_sl.empty())
		return ret_addr;
	
	// create a new queue and insert it to queue group
	// returns a real address
	q = create_queue(q_sl.c_str());
	if(q == NULL)
		return ret_addr;
		
	ret_addr = __g_SKer.Keep((void*)q, SecretType::ST_Q);
	
	return ret_addr;
}

/**
 * @brief Delete queue with specified shadow address.
 * @param queue group pointer.
 * @param queue shadow address.
 * @return VOID.
 */
void pub_DeleteQ(PQ_GROUP q_grp, std::string q_shd_addr) {
	if (q_grp == NULL || q_shd_addr.empty()) {
		return;
	}
	
	PQ q = NULL;
	q = find_queue_by_shadow_addr(q_grp, q_shd_addr.c_str());
	if (q == NULL) {
		return;
	}
	
	erase_q_from_qvector(q_grp, q);
	free_queue(q->m_queue);
	delete q;
	q = NULL;
	
	return;
}

// Public function: 
// create queue node with given node security level
// the new node will be added to the queue with proper security level
// the function returns the node shadow address
std::string pub_CreateQNode(PQ_GROUP q_grp, std::string q_node_sl) {
	std::string ret_addr("");
	
	if (q_grp == NULL || q_node_sl.empty())
		return ret_addr;
	
	// create a node with security level: q_node_sl
	PQ_NODE q_node = create_queue_node(NULL, 0xFF, q_node_sl.c_str());
	if (q_node == NULL)
		return ret_addr;
	
	// generate a node shadow address
	std::string node_shadow_addr = md5_func(q_node->m_id);
	
	// Create a new queue node map, which indicates the mapping relationship between the real address
	// and shadow address of the new node
	Q_NODE_MAP q_ndmap;
	init_qndmap(&q_ndmap);
	strcpy(q_ndmap.m_id, q_node->m_id);
	strcpy(q_ndmap.m_shadow_addr, node_shadow_addr.c_str());
	q_ndmap.m_node = q_node;
	
	/*// find a queue with proper security level
	PQ q = find_queue_by_sl(q_grp, q_node_sl);
	if (q == NULL) 
		return ret_addr;*/
		
	
	PQ q = find_queue_by_sl(q_node_sl, q_grp);
	if (q == NULL){
		printf ("q == NULL\n");
		std::string shadow = pub_CreateQ(q_grp, q_node_sl);
		printf ("shadow = %s\n", shadow.c_str());
		q = find_queue_by_shadow_addr(q_grp, shadow.c_str());
	}
		
	
	// add queue node map (q_dnmap) to queue
	q->m_qnodemap.push_back(q_ndmap);
	// update queue's m_pub_queue member
	q->m_pub_queue.push(node_shadow_addr);
	// add the new node to queue
	add_node_to_queue(q, q_node);
	
	ret_addr = node_shadow_addr;
	
	return ret_addr;
}

/**
 * @brief Create a queue node without adding it to a queue
 * @param q_shd_addr
 * @return Queue node shadow address
 */
std::string pub_CreateQNode(std::string q_node_sl) {
	std::string ret_addr("");
	
	if (q_node_sl.empty())
		return ret_addr;
		
	// create a node with security level: q_node_sl
	PQ_NODE q_node = create_queue_node(NULL, 0xFF, q_node_sl.c_str());
	if (q_node == NULL)
		return ret_addr;
		
	ret_addr = __g_SKer.Keep((void*)q_node, SecretType::ST_QNODE);
	
	return ret_addr;
}

/**
 * @brief Create a queue node by string-formed node infomation without adding it to a queue
 * @param recv_node_info_string
 * @return Queue node shadow address
 */
std::string pub_CreateQNodeFromStr(std::string recv_node_info_string) {
	std::string ret_addr("");
	if (recv_node_info_string.empty())
		return ret_addr;
		
	std::vector<std::string> splitted_str;
	split_string(recv_node_info_string, splitted_str, "|");
	char node_id_buf[128] = {0};
	int node_val = 0xFF;
	char node_sl_buf[128] = {0};
	
	strcpy(node_id_buf, splitted_str[0].c_str());
	node_val = atoi(splitted_str[2].c_str());
	strcpy(node_sl_buf, splitted_str[1].c_str());
	
	PQ_NODE q_node = create_queue_node(node_id_buf, node_val, node_sl_buf);
	if (q_node == NULL)
		return ret_addr;
		
	ret_addr = __g_SKer.Keep((void*)q_node, SecretType::ST_QNODE);
	
	return ret_addr;
}

/**
 * @brief Add node (in SecretKeeper) to a queue (in queue group).
 * @param q_grp: queue group pointer
 * @param q_shd_addr: queue shadow address
 * @param qnode_shd_addr: node shadow address (in SecretKeeper)
 * @return Is successful?
 */
bool pub_AddNodeToQ(PQ_GROUP q_grp, std::string q_shd_addr, std::string qnode_shd_addr) {
	if(q_grp == NULL || q_shd_addr.empty() || qnode_shd_addr.empty())
		return false;
	
	//find corresponding queue
	PQ q = find_queue_by_shadow_addr(q_grp, q_shd_addr.c_str());
	if(q == NULL)
		return false;
	
	PQ_NODE q_node =(PQ_NODE) __g_SKer.Handout(qnode_shd_addr, SecretType::ST_QNODE);
	if(q_node == NULL)
		return false;
		
	// Create a new queue node map, which indicates the mapping relationship between the real address
	// and shadow address of the new node
	Q_NODE_MAP q_ndmap;
	init_qndmap(&q_ndmap);
	strcpy(q_ndmap.m_id, q_node->m_id);
	strcpy(q_ndmap.m_shadow_addr, qnode_shd_addr.c_str());
	q_ndmap.m_node = q_node;
	
	// add queue node map (q_dnmap) to queue
	q->m_qnodemap.push_back(q_ndmap);
	// update queue's m_pub_queue member
	q->m_pub_queue.push(qnode_shd_addr);
	// add the new node to queue
	add_node_to_queue(q, q_node);
	
	return true;
}

/**
 * @brief Add a queue (in SecretKeeper) to queue group
 * @param q_grp
 * @param q_shd_addr: queue shadow address (in SecretKeeper)
 * @return Is successful?
 */
bool pub_AddQtoQGroup(PQ_GROUP q_grp, std::string q_shd_addr) {
	if(q_grp == NULL || q_shd_addr.empty())
		return false;
	
	PQ q =(PQ) __g_SKer.Handout(q_shd_addr, SecretType::ST_Q);
	if(q == NULL)
		return false;
	
	// create a new queue map
	Q_MAP q_map;
	init_qmap(&q_map);
	strcpy(q_map.m_id, q->m_id);
	strcpy(q_map.m_shadow_addr, q_shd_addr.c_str());
	q_map.m_queue = q;
	q_grp->m_qmap.push_back(q_map);
	
	//save shadow address to "public" queue group
	q_grp->m_pub_qgroup.push_back(q_shd_addr);
	
	return true;
}

// print a queue information by queue shadow address
void pub_PrintQueueInfo(PQ_GROUP q_grp, std::string q_addr) {
	if (q_addr.empty() || q_grp == NULL)
		return;
		
	// get real address of corresponding queue
	PQ q = find_queue_by_shadow_addr(q_grp, q_addr.c_str());
	if(q == NULL)	// no proper queue is found
		return;
	
	printf("Queue Info:\n");
	printf("\tID: %s\n", q->m_id);
	printf("\tShadow Addr.: %s\n", md5_func(q->m_id).c_str());
	printf("\tSL: %s\n", q->m_sl);
	printf("\tSize: %d\n", (int)q->m_queue->size());
	printf("\tIdle: %d\n", q->idle);
	
	return;
}

// print a node information by queue shadow address and node shadow address
void pub_PrintQNodeInfo(PQ_GROUP q_grp, std::string q_addr, std::string q_node_addr) {
	if (q_grp == NULL || q_addr.empty() || q_node_addr.empty())
		return;
		
	PQ q = find_queue_by_shadow_addr(q_grp, q_addr.c_str());
	if (q == NULL)
		return;
		
	PQ_NODE q_node = find_node_by_shadow_addr(q, q_node_addr);
	if(q_node == NULL)
		return;
		
	printf("\t\tQ Node ID: %s\n", q_node->m_id);
	printf("\t\tQ Node Value: %#x\n", q_node->m_value);
	printf("\t\tQ SL: %s\n\n", q_node->m_sl);
	
	return;
}


void pub_PrintQueueInfo(Q_GROUP qgrp_obj){
	
	std::vector<std::string>::iterator it_str;
	std::vector<std::string> q_list = pub_GetQueueList(&qgrp_obj);	//get queue group with shadow address
	printf ("q_list.size() = %d\n", q_list.size());
	
	for (it_str = q_list.begin(); it_str != q_list.end(); it_str ++) {
		pub_PrintQueueInfo(&qgrp_obj, (*it_str));
	}
}

void pub_PrintQNodeInfo(Q_GROUP qgrp_obj){
	std::vector<std::string>::iterator it_str;
	std::vector<std::string> q_list = pub_GetQueueList(&qgrp_obj);	//get queue group with shadow address
	//Output information of queues and their nodes
	std::vector<Q_NODE_MAP> tmp_qnodemap;
	std::vector<Q_NODE_MAP>::iterator tmp_it_qnodemap;
	for(it_str = q_list.begin(); it_str != q_list.end(); it_str ++) {
		pub_PrintQueueInfo(&qgrp_obj, (*it_str));
		tmp_qnodemap = pub_GetQNodeMapByShadowAddr(&qgrp_obj, (*it_str));
		for(tmp_it_qnodemap = tmp_qnodemap.begin();
			tmp_it_qnodemap != tmp_qnodemap.end();
			tmp_it_qnodemap ++)
		{
			pub_PrintQNodeInfo(&qgrp_obj, (*it_str), (*tmp_it_qnodemap).m_shadow_addr);
		}
	}
}


// dequeue a queue with specified shadow address: q_shd_addr
std::string pub_Dequeue(PQ_GROUP q_grp, std::string q_shd_addr) {
	std::string ret_str("");
	char buf[64] = {0};
	
	if (q_grp == NULL || q_shd_addr.empty())
		return ret_str;
		
	PQ q = find_queue_by_shadow_addr(q_grp, q_shd_addr.c_str());
	if (q == NULL)
		return ret_str;
	
	// storing dequeued node value
	if (q->m_queue->size() > 0) {
		PQ_NODE deq_node = (PQ_NODE)q->m_queue->front();
		sprintf(buf, "%d", deq_node->m_value); // convert int value to char*
		ret_str = std::string(deq_node->m_id) + std::string("|") + 
					std::string(deq_node->m_sl) + std::string("|") + 
					std::string(buf);
		// update m_qnodemap
		std::vector<Q_NODE_MAP>::iterator it_qnode_map;
		for(it_qnode_map = q->m_qnodemap.begin();
			it_qnode_map != q->m_qnodemap.end(); it_qnode_map ++)
		{
			if(strcmp(deq_node->m_id, (*it_qnode_map).m_id) == 0) {
				std::vector<Q_NODE_MAP>::iterator rm_map_item = it_qnode_map;
				q->m_qnodemap.erase(rm_map_item);
				break;
			}
		}
		// update m_pub_queue
		q->m_pub_queue.pop();
		// free the node
		q->m_queue->pop();
		delete deq_node;
		deq_node = NULL;
	}
		
	return ret_str;
}

void pub_FreeQGroup(PQ_GROUP q_grp) {
	if (q_grp == NULL)
		return;
		
	free_queue_grp(q_grp->m_qgroup);
	
	return;
}

PQ find_queue_by_sl(std::string q_node_sl, PQ_GROUP q_grp){
	
	/*std::vector<std::string> sl_temp;
	int id_temp = -1;
	
	std::vector<std::string>::iterator it_str;
	std::vector<std::string> q_list = pub_GetQueueList(&qgrp_obj);	//get queue group with shadow address
	for (it_str = q_list.begin(); it_str != q_list.end(); it_str ++) {
		//pub_PrintQueueInfo(&qgrp_obj, (*it_str));
		std::string qsl = pub_GetQSLByShadowAddr(&qgrp_obj, (*it_str).c_str());
		printf ("qsl = %s\n", qsl.c_str());
		
		if (isDominated(q_node_sl, qsl) == 0 || isDominated(q_node_sl, qsl) == -1){
			
			printf ("isDominated(q_node_sl, sl_set[%d]) <= 0\n", i);
			
			if (sl_temp.size() == 0 || isDominated(sl_temp, qsl) == 1){
				sl_temp = qsl;
				id_temp = i;
				//printSL(sl_temp);
			}
		}
		
	}
	
	printf ("final result:\n");
	printf ("id_temp = %d\n", id_temp);
	printSL(sl_temp);
	/*if (id_temp != -1 && sl_temp.size() != 0){
		printf ("id_temp = %d\n", id_temp);
	}*/
	
//	return id_temp;*/

	std::string sl_temp;
	//int id_temp = -1;
	
	PQ ret_q = NULL;
	std::vector<PQ>::iterator it_q;
	
	if (q_grp == NULL || q_node_sl.empty()) {
		return ret_q;
	}
	
	for(it_q = q_grp->m_qgroup.begin(); it_q != q_grp->m_qgroup.end(); it_q ++) {
//	for (int i=0; i<q_grp->m_qgroup.size(); i++){
		/*if(q_node_sl == std::string((*it_q)->m_sl)) {
			ret_q = (*it_q);
			return ret_q;
		}*/
		std::vector<PQ>::iterator it_curQ;
		it_curQ = it_q;
		std::string qsl = std::string((*it_curQ)->m_sl);
		if (isDominated(q_node_sl, qsl) == 0 || isDominated(q_node_sl, qsl) == -1){
			
			printf ("isDominated(q_node_sl, %s) <= 0\n", qsl.c_str());
			
			if (sl_temp.size() == 0 || isDominated(sl_temp, qsl) == 1){
				sl_temp = qsl;
				//id_temp = i;
				//ret_q = q_grp->m_qgroup[i];
				ret_q = (*it_q);
				//printSL(sl_temp);
			}
		}
	}
	
	return ret_q;
}

PQ_NODE nonSec_CreateQNode(std::string qnode_sl) {
	PQ_NODE qnode = NULL;
	if(qnode_sl.empty())
		return qnode;
	
	qnode = create_queue_node(NULL, 0xFF, qnode_sl.c_str());
	if(qnode == NULL)
		return qnode;
		
	return qnode;
}

PQ nonSec_CreateQ(std::string q_sl) {
	PQ q = NULL;
	if(q_sl.empty())
		return q;
		
	q = create_queue(q_sl.c_str());
	if(q == NULL)
		return q;
		
	return q;
}

bool nonSec_Enqueue(PQ q, PQ_NODE q_node) {
	if(q == NULL || q_node == NULL)
		return false;
	
	q->m_queue->push(q_node);
	return true;
}

std::string nonSec_Dequeue(PQ q) {
	std::string ret_str("");
	char buf[64]={0};
	
	if(q == NULL)
		return NULL;
		
	if (q->m_queue->size() == 0){
		return ret_str;
	}
	
	PQ_NODE deq_node = q->m_queue->front();
	sprintf(buf, "%d", deq_node->m_value); // convert int value to char*
	ret_str = std::string(deq_node->m_id) + std::string("|") + 
					std::string(deq_node->m_sl) + std::string("|") + 
					std::string(buf);
					
	delete q->m_queue->front();
	q->m_queue->pop();
	
	return ret_str;
}

bool nonSec_AddQToQGroup(PQ_GROUP q_grp, PQ q) {
	if(q_grp == NULL || q == NULL)
		return false;
		
	q_grp->m_qgroup.push_back(q);
	
	return true;
}

bool nonSec_DeleteQ(PQ_GROUP q_grp, std::string q_id) {
	if(q_grp == NULL || q_id.empty())
		return false;
		
	std::vector<PQ>::iterator it;
	PQ del_q = NULL;
	for(it = q_grp->m_qgroup.begin(); it != q_grp->m_qgroup.end(); it++) {
		if (q_id.compare((*it)->m_id) == 0) {
			del_q = (*it);
			q_grp->m_qgroup.erase(it);
			free_queue(del_q->m_queue);
			delete del_q;
			del_q = NULL;
			
			return true;
		}
	}
	
	return false;
}

bool nonSec_DeleteQ(PQ_GROUP q_grp, PQ q) {
	if(q_grp == NULL || q == NULL)
		return false;
		
	return nonSec_DeleteQ(q_grp, q->m_id);
}

void nonSec_FreeQGroup(PQ_GROUP q_grp) {
	if(q_grp == NULL)
		return;
	
	return pub_FreeQGroup(q_grp);
}