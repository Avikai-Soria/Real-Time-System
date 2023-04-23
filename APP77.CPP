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
	cout << "\n *************   A Start    *********************";
	SMARTS.contextSwitchOn();
	for (int j = 0; j < 500; j++)
	{
		for (long i = 0; i < 600000; i++)
			; // Waste 600000 operations time
		SMARTS.contextSwitchOff();
		cout << "A";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   A Finish   *********************";
	SMARTS.contextSwitchOn();
}

void b()
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   B Start    *********************";
	SMARTS.contextSwitchOn();
	for (int j = 0; j < 500; j++) // Waste 600000 operations time
	{
		for (long i = 0; i < 600000; i++)
			;
		SMARTS.contextSwitchOff();
		cout << "B";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   B Finish   *********************";
	SMARTS.contextSwitchOn();
}

void c()
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   C Start    *********************";
	SMARTS.contextSwitchOn();
	for (int j = 0; j < 500; j++)
	{
		for (long i = 0; i < 600000; i++)
			; // Waste 600000 operations time
		SMARTS.contextSwitchOff();
		cout << "C";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   C Finish   *********************";
	SMARTS.contextSwitchOn();
}

void main()
{
	clrscr();
	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, earliesDeadlineFirst);
	SMARTS.declareTask(a, 'A', 5, 70);
	SMARTS.declareTask(b, 'B', 4, 100);
	SMARTS.declareTask(c, 'C', 3, 50);
	SMARTS.runTheTasks();
}