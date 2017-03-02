#include <vector>
#include <queue>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <uuid/uuid.h>
#include <string.h>

#include "q.h"


void init_q(PQ q) {
    if (q == NULL)
        return;

    memset(q->m_id, 0, 128);
    memset(q->m_sl, 0, 128);
    q->m_queue = new std::queue<PQ_NODE>;

    return;
}

void init_qmap(PQ_MAP q_map){
	if (q_map == NULL)
		return;
	memset(q_map->m_id, 0, 128);
	memset(q_map->m_shadow_addr, 0, 128);
	q_map->m_queue = NULL;
	
	return;
}

PQ create_queue(std::vector<PQ> &q_grp, const char* q_sl) {
	PQ pQueue = NULL;
	if (q_sl == NULL){
		printf("create_queue error: null q_sl.\n");
		return pQueue;
    }
	
	pQueue = create_queue(q_sl);
	/*
    uuid_t q_id;
    char uuid_buf[128] = {0};
    PQ pQueue = NULL;

    if (q_sl == NULL){
        printf("create_queue error: null q_sl.\n");
        return pQueue;
    }

    //generate a queue ID
    uuid_generate(q_id);
    memset(uuid_buf, 0, 128);
    uuid_unparse(q_id, uuid_buf);   //convert q_id of uuid_t type into string type

    //create a queue
    pQueue = new Q;

    if (pQueue == NULL) {
        printf("create_queue error: allocating queue failed.\n");
        return pQueue;
    }
    init_q(pQueue);
    strcpy(pQueue->m_id, uuid_buf);

    //copy security level
    strcpy(pQueue->m_sl, q_sl);
	
	pQueue->idle = 0;
	 */

    // push queue into queue group
    q_grp.push_back(pQueue);

    return pQueue;
}

/**
 * @brief Create a queue and return real address
 * @param q_sl
 * @return 
 */
PQ create_queue(const char* q_sl) {
	uuid_t q_id;
    char uuid_buf[128] = {0};
    PQ pQueue = NULL;

    if (q_sl == NULL){
        printf("create_queue error: null q_sl.\n");
        return pQueue;
    }

    //generate a queue ID
    uuid_generate(q_id);
    memset(uuid_buf, 0, 128);
    uuid_unparse(q_id, uuid_buf);   //convert q_id of uuid_t type into string type

    //create a queue
    pQueue = new Q;

    if (pQueue == NULL) {
        printf("create_queue error: allocating queue failed.\n");
        return pQueue;
    }
    init_q(pQueue);
    strcpy(pQueue->m_id, uuid_buf);

    //copy security level
    strcpy(pQueue->m_sl, q_sl);
	
	pQueue->idle = 0;
	
	pthread_mutex_init(&pQueue->mutex, NULL);
	
	return pQueue;
}

void add_node_to_queue(std::vector<PQ> &q_grp, PQ_NODE q_node){
    if(q_node == NULL)
        q_node = create_queue_node(NULL, 0xFF, NULL);   //create a node with default value

    for (unsigned int j=0; j < q_grp.size(); j++) {
        if(strcmp(q_grp[j]->m_sl, q_node->m_sl) == 0) {
            q_grp[j]->m_queue->push(q_node);
            break;
        }
    }
    return;
}

// free the whole queue group
void add_node_to_queue(PQ q, PQ_NODE q_node) {
	if(q == NULL || q_node == NULL)
		return;
	q->m_queue->push(q_node);
	
	return;
}

//free each node of queue
void free_queue(std::queue<PQ_NODE> *q) {
    unsigned int i;
	PQ_NODE qnode = NULL;

    if (q == NULL) {
        return;
    }

    for (i = 0; i < q->size(); i++) {
        if (q->front() != NULL) {
			qnode = q->front();
            delete qnode;
			qnode = NULL;
            q->pop();
        }
    }
    delete q;
	q = NULL;
	return;
}

void print_queue(std::queue<PQ_NODE> *q) {
    int q_size = 0;

    if(q == NULL) {
        printf("print_queue error: null q.\n");
        exit(1);
    }

    q_size = q->size();
    for (int j = 0; j < q_size; j++) {
        PQ_NODE q_node = q->front();
        printf("\t\tQ Node ID: %s\n", q_node->m_id);
        printf("\t\tQ Node Value: %#x\n", q_node->m_value);
        printf("\t\tQ SL: %s\n\n", q_node->m_sl);
        //q->front() has to be delete for outputing next node
        delete q_node;
		q_node = NULL;
        q->pop();
    }

    return;
}

/////////////////////////////////////////////////////////////////////////////////