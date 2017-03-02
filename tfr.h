#ifndef TFR_H
#define TFR_H

#include <string>
#include <vector>
#include <stdio.h>
#include "qgroup.h"

#define MAX_IDLE	20

bool tfrScheduAlg(PQ_GROUP q_grp, std::string sl);
bool sec_low_tfrScheduAlg(PQ_GROUP q_grp, std::string sl);
bool sec_non_tfrScheduAlg(PQ_GROUP q_grp, std::string sl);

void testTfrScheduAlg(PQ_GROUP, int);
void testSecLowTfrScheduAlg(PQ_GROUP, int);
void testSecNonTfrScheduAlg(PQ_GROUP, int);

#endif