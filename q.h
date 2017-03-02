#ifndef Q_H
#define Q_H

#include <vector>
#include <queue>
#include <string>
#include <pthread.h>
#include "qnode.h"

typedef struct _Q {
    char m_id[128];
    char m_sl[128];   //security level
	std::queue<PQ_NODE> *m_queue;	//the queue storing real node address
	std::vector<Q_NODE_MAP> m_qnodemap;	//protected member storing mapping relationships between real addr and shadow addr
	std::queue<std::string> m_pub_queue;	//public member for accessing queue nodes (shadow node address)
	int idle;
	pthread_mutex_t mutex;
} Q, *PQ;

//Q_MAP maps real address of queue to a shadow address
typedef struct _Q_MAP {
	char m_id[128];	//queue ID
	PQ m_queue;		//real address of queue
	char m_shadow_addr[128];	//shadow address of queue
} Q_MAP, *PQ_MAP;

void init_q(PQ);
void init_qmap(PQ_MAP);

/**
 * @brief Create a queue with specified security level, and add the queue to specified queue group.
 * @param Queue group.
 * @param Security level string.
 * @return Created queue. If failed, NULL pointer is returned.
 */
PQ create_queue(std::vector<PQ> &, const char*);
PQ create_queue(const char*);
void add_node_to_queue(std::vector<PQ> &, PQ_NODE);
void add_node_to_queue(PQ, PQ_NODE);

/**
 * @brief Free each node of the queue, including queue itself.
 * @param Queue pointer.
 * @return VOID.
 */
void free_queue(std::queue<PQ_NODE> *);
void print_queue(std::queue<PQ_NODE> *);

#endif