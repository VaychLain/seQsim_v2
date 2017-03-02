#ifndef SL_H
#define SL_H

#include <string>
#include <vector>
#include <glib.h>
//#include <qgroup.h>

/**
 * @brief compare security level 
 * @param sl_1
 * @param sl_2
 * @return   0:	sl_1=sl_2 	
 * 			 1:	sl_1>sl_2	 
 * 			-1:	sl_1<sl_2 	 
 * 			-2:	no
 */
int is_dominated_help(std::vector<std::string> sl_1, std::vector<std::string> sl_2);

//int isDominated(std::string sl_1, std::string sl_2);

int isDominated(std::string sl1, std::string sl2);

/**
 * @brief getTargetQ for test
 * @param sl
 * @param slSet
 * @return 
 */
int getTargetQForSL(std::vector<std::string> q_node_sl, std::vector<std::vector<std::string> > sl_set);

/**
 * @brief getTargetQ for use
 * @param sl
 * @param slSet
 * @return id of queue
 */
//int getTargetQForSL(std::string q_node_sl, Q_GROUP qgrp_obj);

std::vector<std::string> genVEE(int m);
std::vector<std::string> genSL(int n);
bool genSLCStr(int sl_dim, char* out_buf);
std::string genSLStr(int);

/**
 * @brief generate the set for sl
 * @param n	size for sl
 * @param m	tuple for each sl
 * @return 
 */
std::vector<std::vector<std::string> > genSLSet(int n, int m);

void printSL(std::vector<std::string> sl);

void printSLSet(std::vector<std::vector<std::string> > sl_set);

/**
 * @brief 
 * @param n: number of test cases
 */
void testSLIsDominated(int, int);

void testGetTargetQForSL(int n);

void testSLGen(int);

void slGenToFile(int, int);
void slGenFromFile(std::string);


void timeToFile(std::string filename, gdouble elapsed_time);

#endif