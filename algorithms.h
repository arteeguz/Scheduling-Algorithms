#ifndef Algorithms_H
#define Algorithms_H
#include "process.h"

int firstComeFirstServe(Process processArray[], int numJobs);
int roundRobin(Process processArray[], int numJobs, int quantum);

#endif