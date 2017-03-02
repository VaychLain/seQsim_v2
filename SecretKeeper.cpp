#include "SecretKeeper.h"

SecretKeeper::SecretKeeper()
{
}

SecretKeeper::~SecretKeeper()
{
}

/**
 * @brief Wrap a queue node map
 * @param qnodemap
 * @param p_qnode
 * @return queue node shadow address
 */
std::string SecretKeeper::wrap(PQ_NODE_MAP qnodemap, PQ_NODE p_qnode){
	if(p_qnode == NULL) {
		return std::string("");
	}
	
	init_qndmap(qnodemap);
	std::string shadow_addr(md5_func(qnodemap->m_id));
	strcpy(qnodemap->m_id, p_qnode->m_id);
	qnodemap->m_node = p_qnode;
	strcpy(qnodemap->m_shadow_addr, shadow_addr.c_str());
	
	return shadow_addr;
}

std::string SecretKeeper::wrap(PQ_MAP qmap, PQ pq) {
	if(pq == NULL) {
		return std::string("");
	}
	
	init_qmap(qmap);
	std::string shadow_addr(md5_func(pq->m_id));
	strcpy(qmap->m_id, pq->m_id);
	qmap->m_queue = pq;
	strcpy(qmap->m_shadow_addr,shadow_addr.c_str());
	
	return shadow_addr;
}

/**
 * @brief Keep the real information of the queue node
 * @param p_qnode
 * @return queue node shadow address
 */
std::string SecretKeeper::keep_helper(PQ_NODE p_qnode) {
	if(p_qnode == NULL) {
		return std::string("");
	}
	
	Q_NODE_MAP qnodemap;
	std::string shd_addr = this->wrap(&qnodemap, p_qnode);
	if(shd_addr.empty())
		return std::string("");
	
	this->m_qnodemap.push_back(qnodemap);
	
	return shd_addr;
}

/**
 * @brief Keep the real information of the queue
 * @param pq
 * @return 
 */
std::string SecretKeeper::keep_helper(PQ pq) {
	if(pq == NULL) {
		return std::string("");
	}
	
	Q_MAP qmap;
	std::string shd_addr = this->wrap(&qmap, pq);
	if(shd_addr.empty())
		return std::string("");
		
	this->m_qmap.push_back(qmap);
	
	return shd_addr;
}

/**
 * @brief Hand out the secret information (queue node or queue) specified by given shadow address
 * @param shd_addr
 */
void* SecretKeeper::handout_qnode_helper(std::string shd_addr) {
	if(shd_addr.empty())
		return NULL;
		
	void *ret_obj = NULL;
	
	std::vector<Q_NODE_MAP>::iterator it;
	for(it = this->m_qnodemap.begin(); it != this->m_qnodemap.end(); it ++) {
		if(shd_addr.compare((*it).m_shadow_addr) == 0) {
			ret_obj = (void*)((*it).m_node);
			this->m_qnodemap.erase(it);
			break;
		}
	}//for 
	
	return ret_obj;
}

void* SecretKeeper::handout_q_helper(std::string shd_addr) {
	if(shd_addr.empty())
		return NULL;
		
	void *ret_obj = NULL;
	
	std::vector<Q_MAP>::iterator it;
	for(it = this->m_qmap.begin(); it != this->m_qmap.end(); it ++) {
		if(shd_addr.compare((*it).m_shadow_addr) == 0) {
			ret_obj = (void*)((*it).m_queue);
			this->m_qmap.erase(it);
			break;
		}
	}//for
	
	return ret_obj;
}

/**
 * @brief Keep real address of the data specified by obj_ptr
 * @param obj_ptr
 * @param ST_type
 * @return The shadow address
 */
std::string SecretKeeper::Keep(void *obj_ptr, int ST_type) {
	if (obj_ptr == NULL)
		return std::string("");
		
	std::string shd_addr;
	
	switch(ST_type) {
		case SecretType::ST_QNODE:
			shd_addr = this->keep_helper((PQ_NODE)obj_ptr);
			return shd_addr;
		case SecretType::ST_Q:
			shd_addr = this->keep_helper((PQ)obj_ptr);
			return shd_addr;
		default:
			return std::string("");
	}
	
	return std::string("");
}

void* SecretKeeper::Handout(std::string shd_addr, int ST_type) {
	if(shd_addr.empty())
		return NULL;
		
	switch(ST_type) {
		case SecretType::ST_QNODE:
			return this->handout_qnode_helper(shd_addr);
		case SecretType::ST_Q:
			return this->handout_q_helper(shd_addr);
		default:
			return NULL;
	}
	
	return NULL;
}