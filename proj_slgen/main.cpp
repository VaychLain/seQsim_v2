#include <stdio.h>

#include "../sl.h"


int main(int argc, char **argv)
{
	
	int caseNum = 10000;
//	testSLGen(20);
		
	/*slGenToFile(3, caseNum);
	slGenToFile(5, caseNum);
	slGenToFile(10, caseNum);
	slGenToFile(15, caseNum);
	slGenToFile(20, caseNum);
	slGenToFile(25, caseNum);
	slGenToFile(30, caseNum);*/
	
	gulong* se;
	gdouble elapsed_time;
	GTimer * timer = g_timer_new();
	g_timer_start(timer);
	g_timer_stop (timer);
	elapsed_time = g_timer_elapsed (timer,se);
	printf("time elapsed: %lf\n", elapsed_time);
	timeToFile("tfr.txt", elapsed_time);
	
	//read file example
	/*std::string filename("../../sldata/sl_10.txt");
	slGenFromFile(filename);*/
	
//	testSLIsDominated(10, 5);
	
	return 0;
}
