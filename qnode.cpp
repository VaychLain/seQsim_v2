#include "qnode.h"
#include <uuid/uuid.h>
#include <stdlib.h>
#include <string.h>

void init_q_node(PQ_NODE q_node) {
    if (q_node == NULL)
        return;

    memset(q_node->m_id,0,128);
    memset(q_node->m_sl, 0, 128);
    q_node->m_value = 0;

    return;
}

void init_qndmap(PQ_NODE_MAP q_ndmap) {
	if(q_ndmap == NULL)
		return;
		
	memset(q_ndmap->m_id, 0, 128);
	memset(q_ndmap->m_shadow_addr, 0, 128);
	q_ndmap->m_node = NULL;
	
	return;
}

PQ_NODE create_queue_node(char *n_id, int n_val, const char *n_sl){
    n_val = 0xFF;   //default
    char buf[128] = {"NORMAL"}; //default
    uuid_t uuid_node;
    char node_id_buf[128] = {0};
    PQ_NODE q_node = NULL;

    //generate node ID
	if(n_id == NULL) {
		uuid_generate(uuid_node);
		uuid_unparse(uuid_node, node_id_buf);
	}
	else {
		strcpy(node_id_buf, n_id);
	}

    //allocate a node
    q_node = new Q_NODE;
    if (q_node == NULL)
        return q_node;

    init_q_node(q_node);

    strcpy(q_node->m_id, node_id_buf);
    if (n_sl == NULL)
        strcpy(q_node->m_sl, buf);
    else
        strcpy(q_node->m_sl, n_sl);
    q_node->m_value = n_val;

    return q_node;
}
