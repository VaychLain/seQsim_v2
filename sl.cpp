#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h> 

#include "sl.h"
#include "helps.h"
#include "globals.h"

int is_dominated_help(std::vector<std::string> sl_1, std::vector<std::string> sl_2){
	int countA = 0, countB = 0, countC = 0;
	int size_sl_1 = sl_1.size();
	int size_sl_2 = sl_2.size();
	if (size_sl_1 == 0 || size_sl_2 == 0)
		return -2;
	
	if (size_sl_1 != size_sl_2){
		return -2;
	}
	
	for (int i=0; i<size_sl_1; i++){
		if (sl_1[i] == sl_2[i]){
			countA++;
		}else if (sl_1[i] == "00" || sl_2[i] == "ff"){
			countB++;
		}else if (sl_1[i] == "ff" || sl_2[i] == "00"){
			countC++;
		}else{
			return -2;
		}
	}
	
	if (countA == size_sl_1){
		return 0;
	}else if (countA + countB == size_sl_1){
		return -1;
	}else if (countA + countC == size_sl_1){
		return 1;
	}
	
	return -2;
}

int isDominated(std::string sl1, std::string sl2) {
	int ret_val;
	std::vector<std::string> sl_1, sl_2;
	
	split_string(sl1, sl_1, ",");
	split_string(sl2, sl_2, ",");
	
	ret_val = is_dominated_help(sl_1, sl_2);
	return ret_val;
}

/*
int isDominated_f(std::string sl1, std::string sl2){
	
	std::vector<std::string> sl_1, sl_2;
	char * p = NULL;
	const char * split = ",";
	
	p = strtok((char *)sl1.c_str(), split);
	while(p != NULL){
		//printf ("%s\n", p);
		sl_1.push_back(p);
		p = strtok(NULL, split);
	}
	
	p = strtok((char *)sl2.c_str(), split);
	while(p != NULL){
		//printf ("%s\n", p);
		sl_2.push_back(p);
		p = strtok(NULL, split);
	}
	
	return isDominated(sl_1, sl_2);
}
 * */

int getTargetQForSL(std::vector<std::string> q_node_sl, 
					std::vector<std::vector<std::string> > sl_set){
	
	std::vector<std::string> sl_temp;
	int id_temp = -1;
	
	//printSL(sl_temp);
	
	for(int i=0; i<sl_set.size(); i++){
		if (is_dominated_help(q_node_sl, sl_set[i]) == 0 || is_dominated_help(q_node_sl, sl_set[i]) == -1){
			
			printf ("isDominated(q_node_sl, sl_set[%d]) <= 0\n", i);
			
			if (sl_temp.size() == 0 || is_dominated_help(sl_temp, sl_set[i]) == 1){
				sl_temp = sl_set[i];
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
	
	return id_temp;
}




std::vector<std::string> genVEE(int m){
	std::vector<std::string> vee;
	char buf[10] = {0};
	
	
	for (int i=0; i<m-2; i++){
		memset(buf, 0, 10);
		
		//it's should in for, otherwise prefix will be changed
		std::string prefix = "V";
		
		if (i < (m-2)/2){
			sprintf (buf, "%d", i);
			
		}else {
			sprintf (buf, "%c", 'a' + i - (m-2)/2);
		}
		
		vee.push_back(prefix.append(buf));
	}
	
	vee.push_back("00");
	vee.push_back("ff");
	
	/*std::vector<std::string> vee;
	
	vee.push_back("va");
	vee.push_back("vb");
	vee.push_back("v0");
	vee.push_back("00");
	vee.push_back("ff");*/
	
	return vee;
}

std::vector<std::string> genSL(int n){
	
	std::vector<std::string> sl;
	std::vector<std::string> vee = genVEE(5);
	
	//it can't be set, otherwise same data generated
//	srand(time(0));
	
	for (int i=0; i<n; i++){
		sl.push_back(vee[rand() % vee.size()]);
	}
	
	return sl;
}

/**
 * @brief 
 * @param sl_dim: Dimension of security level
 * @param out_buf: Output buffer
 * @return 
 */
bool genSLCStr(int sl_dim, char* out_buf) {
	char temp_buf[10]={0};
	
	if(sl_dim == 0 || out_buf == NULL) {
		return false;
	}
	
	srand(time(0));
	
	for(int i = 0; i < sl_dim - 1; i++) {
		strcat(temp_buf, __g_VEEenum[rand() % VEE_ENUM_DIM]);
		strcat(temp_buf, ",");
	}
	strcat(temp_buf, __g_VEEenum[rand() % VEE_ENUM_DIM]);
	
	strcpy(out_buf, temp_buf);
	
	return true;
}

std::string genSLStr(int n){
	
	std::string sl("");
//	srand(time(0));

	std::vector<std::string> vee = genVEE(5);
	
/*	std::vector<std::string> vee;
	
	vee.push_back("va");
	vee.push_back("vb");
	vee.push_back("v0");
	vee.push_back("00");
	vee.push_back("ff");*/
	
	for (int i=0; i<n-1; i++){
		sl.append(vee[rand() % vee.size()]);
		
		sl.append(",");
//		sl.push_back(vee[rand()%(vee.size())]);
	}
	sl.append(vee[rand() % vee.size()]);
	
	return sl;
}

std::vector<std::vector<std::string> > genSLSet(int n, int m){
	std::vector<std::vector<std::string> > sl_set;
	
	for (int i=0; i<n; i++){
		sl_set.push_back(genSL(m));
	}
	
	return sl_set;
}

void printSL(std::vector<std::string> sl){
	//output data in sl
	//printf ("print sl: ");
	for (int i=0; i<sl.size(); i++){
		printf ("%s ", sl[i].c_str());
	}
	printf ("\n");
}

void printSLSet(std::vector<std::vector<std::string> > sl_set){
	for (int i=0; i<sl_set.size(); i++){
		printf ("%d: ", i);
		printSL(sl_set[i]);
	}
	printf ("\n");
}

void testSLIsDominated(int n, int m){
	
	std::vector<std::string> sl_1, sl_2;

	for (int i=0; i<n; i++){
		
		printf ("\n-----------------%d--------------\n", i);
		
		//sl generateSL
		sl_1 = genSL(m);
		sl_2 = genSL(m);
		
		printSL(sl_1);
		printSL(sl_2);
		
		//sl test	
		int result = is_dominated_help(sl_1, sl_2);
		printf("result: %d ", result);
		switch(result){
			case 0:
				printf ("sl_1 == sl_2\n");break;
			case 1:
				printf ("sl_1 > sl_2\n");break;
			case -1:
				printf ("sl_1 < sl_2\n");break;
			case -2:
				printf ("no\n");break;
		}
	}
}



void testGetTargetQForSL(int n){
	
	std::vector<std::string> q_node_sl; 
	std::vector<std::vector<std::string> > sl_set = genSLSet(20, 3);
	
	printf ("\nsl_set:(%d)\n", sl_set.size());
	printSLSet(sl_set);
	
	for (int i=0; i<n; i++){
		printf ("\n-----------------%d--------------\n", i);
		q_node_sl = genSL(3);
		printf ("q_node_sl: ");
		printSL(q_node_sl);
		getTargetQForSL(q_node_sl, sl_set);
	}
	//genSLSet(10, 3);
	
}

void testSLGen(int n){
	std::vector<std::string> q_node_sl; 
	
	for (int i=0; i<n; i++){
		printf ("\n-----------------testSLGen %d--------------\n", i);
		q_node_sl = genSL(3);
		printf ("q_node_sl: ");
		printSL(q_node_sl);		
	}
}

/**
 * @brief 
 * @param m number of turple
 * @param n number of cases
 */
void slGenToFile(int m, int n){
	FILE * fp;
	char buf[10];
	std::string filename("../../sldata/sl_");
	
	sprintf (buf, "%d", m);
	filename.append(buf);
	filename.append(".txt");
	
	if ((fp = fopen(filename.c_str(), "w")) == NULL){
		printf ("error!");
	}
	
	for (int i=0; i<n; i++){
		std::string q_node_sl = genSLStr(m);
//		printf ("%s\n", q_node_sl.c_str());
		fprintf (fp, "%s\n", q_node_sl.c_str());
		fflush(fp);
	}
	
	printf ("completed\n");
	
	fclose(fp);
}

void slGenFromFile(std::string filename){
	FILE * fp;
	char buf[100];
	if ((fp = fopen(filename.c_str(), "rb")) == NULL){
		printf ("error!");
	}
	
	while (!feof(fp)){
		fscanf(fp, "%s\n", buf);
		printf ("%s\n", buf);
	}
	
	printf ("slGenFromFile compelted\n");
	
	fclose(fp);
}


void timeToFile(std::string file, gdouble elapsed_time){
	FILE * fp;
	std::string filenname("../../result/");
	
	int status = mkdir("../../result", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
	filenname.append(file);
	if ((fp = fopen(filenname.c_str(), "a")) == NULL){
		printf ("error!");
	}
	
	fprintf (fp, "%lf\n", elapsed_time);
	
	fclose(fp);
}

