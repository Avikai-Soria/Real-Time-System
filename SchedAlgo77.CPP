/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory                 */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum                  */
/* Jerusalem College of Technology, 5759-64 (1999)                            */
/* SchedAlgo64.CPP, short-term scheduler algorithms                */
/****************************************************************/

#include "smarts77.h"


int roundRobin()
// Round Robin short-term algorithm
{
	int count;
	int nextTask = (SMARTS.getCurrentTask() + 1) % SMARTS.getTotalTasks();
	for (count = 0;
		 SMARTS.getStatus(nextTask) != READY && count < SMARTS.getTotalTasks();
		 count++)
		nextTask = ++nextTask % SMARTS.getTotalTasks();
	if (count == SMARTS.getTotalTasks()) // no found READY task to run
		nextTask = SMARTS.getTotalTasks();
	return nextTask;
}

/*
int roundRobin()
{
    int nextTask = (SMARTS.getCurrentTask() + 1) % SMARTS.getTotalTasks();
    while (SMARTS.getStatus(nextTask) != READY) {
        nextTask = (nextTask + 1) % SMARTS.getTotalTasks();
        if (nextTask == SMARTS.getCurrentTask()) {
            return SMARTS.getTotalTasks();
        }
    }
    return nextTask;
}
*/

/*
void updateAllTasks() {
	for (int i = 0; i < SMARTS.getTotalTasks(); i++) {
		SMARTS.setDeadline(i, SMARTS.getDeadline(i) - 1);
	}
	int curr = SMARTS.getCurrentTask();
}
*/

int earliesDeadlineFirst() {
	int lowest = MAXINT;
	int nextTask = SMARTS.getTotalTasks();
	for (int i = 0; i < SMARTS.getTotalTasks(); i++) {
		if(SMARTS.getDeadline(i) < lowest && SMARTS.getStatus(i) == READY) {
			nextTask = i;
			lowest = SMARTS.getDeadline(i);
		}
	}
	return nextTask;
}
