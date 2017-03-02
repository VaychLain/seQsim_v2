#ifndef Q_NODE_H
#define Q_NODE_H

typedef struct _Q_NODE {
    char m_id[128];
    int m_value;
    char m_sl[128];
} Q_NODE, *PQ_NODE;

//Q_NODE_MAP maps real address of queue node to a shadow address
typedef struct _Q_NODE_MAP {
	char m_id[128];	//queue node ID
	PQ_NODE m_node;		//real address of a queue node
	char m_shadow_addr[128];	//shadow address of queue node
} Q_NODE_MAP, *PQ_NODE_MAP;

void init_q_node(PQ_NODE);
void init_qndmap(PQ_NODE_MAP);
PQ_NODE create_queue_node(char *, int, const char *);

#endif