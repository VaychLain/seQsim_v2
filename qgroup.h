#ifndef Q_GROUP_H
#define Q_GROUP_H

#include <vector>
#include <queue>
#include <string>
#include "q.h"
#include "qnode.h"
#include "sl.h"

typedef struct _Q_GROUP {
    std::vector<PQ> m_qgroup;		//private member
    std::vector<Q_MAP> m_qmap;		//protected member
	std::vector<std::string> m_pub_qgroup;		//public member for accessing queues
} Q_GROUP, *PQ_GROUP;

PQ find_queue_by_shadow_addr(PQ_GROUP, const char*);
PQ find_queue_by_sl(PQ_GROUP, std::string);
PQ find_queue_by_sl(std::string, PQ_GROUP);
bool erase_q_from_qvector(PQ_GROUP q_grp, PQ q);
PQ_NODE find_node_by_shadow_addr(PQ_GROUP, std::string);
PQ_NODE find_node_by_shadow_addr(PQ, std::string);
void free_queue_grp(std::vector<PQ> &);

std::string pub_GetQSLByShadowAddr(PQ_GROUP, const char*);
std::string pub_GetQueueFromQgrpBySL(PQ_GROUP, std::string);
std::vector<std::string>& pub_GetQueueList(PQ_GROUP);
std::vector<Q_NODE_MAP>& pub_GetQNodeMapByShadowAddr(PQ_GROUP, std::string);
std::string pub_CreateQ(PQ_GROUP, std::string);
std::string pub_CreateQ(std::string);
std::string pub_CreateQNodeFromStr(std::string recv_node_info_string);
std::string pub_CreateQNode(PQ_GROUP, std::string);
std::string pub_CreateQNode(std::string);
bool pub_AddNodeToQ(PQ_GROUP q_grp, std::string q_shd_addr, std::string qnode_shd_addr);
bool pub_AddQtoQGroup(PQ_GROUP q_grp, std::string q_shd_addr);
void pub_DeleteQ(PQ_GROUP, std::string);
void pub_PrintQueueInfo(PQ_GROUP, std::string);
void pub_PrintQNodeInfo(PQ_GROUP, std::string, std::string);
void pub_PrintQueueInfo(Q_GROUP);
void pub_PrintQNodeInfo(Q_GROUP);
std::string pub_Dequeue(PQ_GROUP, std::string);

int pub_GetQIdleByShadowAddr(PQ_GROUP, const char*);
bool pub_UpdateQIdleByShadowAddr(PQ_GROUP, const char*);
int pub_GetQSizeByShadowAddr(PQ_GROUP, const char*);

void pub_FreeQGroup(PQ_GROUP);

PQ_NODE nonSec_CreateQNode(std::string qnode_sl);
PQ nonSec_CreateQ(std::string q_sl);
bool nonSec_Enqueue(PQ q, PQ_NODE q_node);
std::string nonSec_Dequeue(PQ q);
bool nonSec_AddQToQGroup(PQ_GROUP q_grp, PQ q);
bool nonSec_DeleteQ(PQ_GROUP q_grp, std::string q_id);
bool nonSec_DeleteQ(PQ_GROUP q_grp, PQ q);
void nonSec_FreeQGroup(PQ_GROUP q_grp);

#endif