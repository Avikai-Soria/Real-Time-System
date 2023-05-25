/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory            */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum              */
/* Jerusalem College of Technology, 5759-64 (1999-03)               */
/* update  Tishrey   5777                                           */
/* APP77.CPP, an application to demonstrate SMARTS77  functioning   */
/********************************************************************/
#include "smarts77.h"

// user Functions
void a()
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   A Start    *********************\n";
	SMARTS.contextSwitchOn();
	for (int j = 0; j < 50; j++)
	{
		for (long i = 0; i < 600000; i++)
			; // Waste 600000 operations time
		SMARTS.contextSwitchOff();
		cout << "A";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   A Finish   *********************\n";
	SMARTS.contextSwitchOn();
}

void b()
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   B Start    *********************\n";
	SMARTS.contextSwitchOn();
	for (int j = 0; j < 50; j++) // Waste 600000 operations time
	{
		for (long i = 0; i < 600000; i++)
			;
		SMARTS.contextSwitchOff();
		cout << "B";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   B Finish   *********************\n";
	SMARTS.contextSwitchOn();
}

void c()
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   C Start    *********************\n";
	SMARTS.contextSwitchOn();
	for (int j = 0; j < 50; j++)
	{
		for (long i = 0; i < 600000; i++)
			; // Waste 600000 operations time
		SMARTS.contextSwitchOff();
		cout << "C";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   C Finish   *********************\n";
	SMARTS.contextSwitchOn();
}

void main()
{
	clrscr();
	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, rate_monotonic_scheduling);
	SMARTS.declareTask(a, 'A', 112, 1);
	SMARTS.declareTask(b, 'B', 224, 2);
	SMARTS.declareTask(c, 'C', 448, 3);
	SMARTS.runTheTasks();
}

/*
Both fail:
SMARTS.declareTask(a, 'A', 50, 3);
SMARTS.declareTask(b, 'B', 100, 4);
SMARTS.declareTask(c, 'C', 200, 5);
*/

/*
RR fail and EDF succeed:
SMARTS.declareTask(a, 'A', 224, 3);
SMARTS.declareTask(b, 'B', 224, 5);
SMARTS.declareTask(c, 'C', 784, 4);
*/

/*
Both succeed:
SMARTS.declareTask(a, 'A', 336, 5);
SMARTS.declareTask(b, 'B', 336, 3);
SMARTS.declareTask(c, 'C', 336, 4);
*/

/*
Teacher example:
SMARTS.declareTask(a, 'A', 30, 2);
SMARTS.declareTask(b, 'B', 30, 3);
SMARTS.declareTask(c, 'C', 30, 4);
*/