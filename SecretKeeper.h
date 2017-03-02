#ifndef SECRETKEEPER_H
#define SECRETKEEPER_H

#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "helps.h"
#include "qnode.h"
#include "q.h"
#include "qgroup.h"

class SecretType {
public:
	static const int ST_QNODE = 0x01;
	static const int ST_Q = 0x02;
private:
	SecretType(){;}	//Forbid to create object of this class
};

/**
 * @class SecretKeeper
 * @author ld
 * @date 27/12/16
 * @file SecretKeeper.h
 * @brief This class keeps some data with security contraints temporarily, such as 
 * Q_NODE_MAP and Q_MAP. E.g., When a user create a node (or a queue), the real address
 * of the node (or queue) is stored in a SecretKeeper object. When a node (or a queue) 
 * is fetched from the SecretKeeper object, it will be removed from the object.
 */
class SecretKeeper
{
private:
	std::vector<Q_NODE_MAP> m_qnodemap;
	std::vector<Q_MAP> m_qmap;
private:
	std::string wrap(PQ_NODE_MAP qnodemap, PQ_NODE p_qnode);
	std::string wrap(PQ_MAP qmap, PQ pq);
	std::string keep_helper(PQ_NODE p_qnode);
	std::string keep_helper(PQ pq);
	void* handout_qnode_helper(std::string shd_addr);
	void* handout_q_helper(std::string shd_addr);
public:
	SecretKeeper();
	~SecretKeeper();
	std::string Keep(void *obj_ptr, int ST_type);
	void* Handout(std::string shd_addr, int ST_type);
};

#endif // SECRETKEEPER_H
