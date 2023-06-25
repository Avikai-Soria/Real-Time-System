/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory            */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum              */
/* Jerusalem College of Technology, 5759-64 (1999-03)               */
/* update  Tishrey   5777                                           */
/* APP77.CPP, an application to demonstrate SMARTS77  functioning   */
/********************************************************************/

#include "smarts77.h"

Mutex ioMutex;

Event evAtoB, evBtoC, evCtoD, evDtoE, evFtoE;

void clearLog()
{
	FILE *f = fopen("log.txt", "w"); // w  == write mode (truncate the file)
	fclose(f);
}

void writeToLog(char *str)
{
	FILE *f = fopen("log.txt", "a"); // a  == append
	fprintf(f, str);
	fclose(f);
}

// user Functions
void a()
{
	int j;
	ioMutex.Acquire();
	cout << "\n *************   A Start    *********************\n";
	writeToLog("\n *************   A Start    *********************\n");
	ioMutex.Release();
	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "A";
		writeToLog("A");
		ioMutex.Release();
	}

	char r;
	writeToLog("\nHello there! I am A and I WAIT to B\n");
	evAtoB.wait(r);
	writeToLog("Hello there! I am A and B let me go\n");

	writeToLog("\nHello there! I am A and I acquire SMARTS.mutexes[0]\n");
	SMARTS.mutexes[0].Acquire();
	writeToLog("Hello there! I am A and I got SMARTS.mutexes[0]\n");
	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "A";
		writeToLog("A");
		ioMutex.Release();
	}

	writeToLog("\nHello there! I am A and I release SMARTS.mutexes[0]\n");
	//printf("\nCurrent roundtime for A: %d\n", SMARTS.getRoundTime(SMARTS.getCurrentTask()));
	SMARTS.mutexes[0].Release();
	writeToLog("SMARTS.mutexes[0] was released.\n");

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "A";
		writeToLog("A");
		ioMutex.Release();
	}

	ioMutex.Acquire();
	cout << "\n *************   A Finish   *********************\n";
	writeToLog("\n *************   A finish    *********************\n");
	ioMutex.Release();
}

void b()
{
	int j;
	ioMutex.Acquire();
	cout << "\n *************   B Start    *********************\n";
	writeToLog("\n *************   B Start    *********************\n");
	ioMutex.Release();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "B";
		writeToLog("B");
		ioMutex.Release();
	}

	char r;
	writeToLog("\nHello there! I am B and I WAIT to C\n");
	evBtoC.wait(r);
	writeToLog("Hello there! I am B and C let me go\n");

	writeToLog("Hello there! I am B and I acquire SMARTS.mutexes[0]\n");
	SMARTS.mutexes[0].Acquire();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "B";
		writeToLog("B");
		ioMutex.Release();
	}

	char d;
	writeToLog("\nHello there! I am B and I send to A\n");
	evAtoB.send('A', &d, 0);

	writeToLog("Hello there! I am B and I acquire SMARTS.mutexes[1]\n");
	SMARTS.mutexes[1].Acquire();
	writeToLog("Hello there! I am B and I got SMARTS.mutexes[1]\n");

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "B";
		writeToLog("B");
		ioMutex.Release();
	}

	writeToLog("\nHello there, I am B and I release SMARTS.mutexes[1]\n");
	SMARTS.mutexes[1].Release();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "B";
		writeToLog("B");
		ioMutex.Release();
	}

	writeToLog("\nHello there, I am B and I release SMARTS.mutexes[0]\n");
	//printf("\nCurrent roundtime for B: %d\n", SMARTS.getRoundTime(SMARTS.getCurrentTask()));
	SMARTS.mutexes[0].Release();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "B";
		writeToLog("B");
		ioMutex.Release();
	}

	ioMutex.Acquire();
	cout << "\n *************   B Finish   *********************\n";
	writeToLog("\n *************   B finish    *********************\n");
	ioMutex.Release();
}

void c()
{
	int j;
	ioMutex.Acquire();
	cout << "\n ************* C Start *********************\n";
	writeToLog("\n ************* C Start *********************\n");
	ioMutex.Release();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "C";
		writeToLog("C");
		ioMutex.Release();
	}

	char r;
	writeToLog("\nHello there! I am C and I WAIT to D\n");
	evCtoD.wait(r);
	writeToLog("Hello there! I am C and D let me go\n");

	writeToLog("Hello there! I am C and I acquire SMARTS.mutexes[1]\n");
	SMARTS.mutexes[1].Acquire();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "C";
		writeToLog("C");
		ioMutex.Release();
	}

	char d;
	writeToLog("\nHello there! I am C and I send to B\n");
	evBtoC.send('B', &d, 0);

	writeToLog("Hello there! I am C and I acquire SMARTS.mutexes[2]\n");
	SMARTS.mutexes[2].Acquire();
	writeToLog("Hello there! I am C and I got SMARTS.mutexes[2]\n");

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "C";
		writeToLog("C");
		ioMutex.Release();
	}

	writeToLog("\nHello there, I am C and I release SMARTS.mutexes[2]\n");
	SMARTS.mutexes[2].Release();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "C";
		writeToLog("C");
		ioMutex.Release();
	}

	//printf("\nCurrent roundtime for C: %d\n", SMARTS.getRoundTime(SMARTS.getCurrentTask()));
	writeToLog("\nHello there, I am C and I release SMARTS.mutexes[1]\n");
	SMARTS.mutexes[1].Release();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "C";
		writeToLog("C");
		ioMutex.Release();
	}

	ioMutex.Acquire();
	cout << "\n *************   C Finish   *********************\n";
	writeToLog("\n *************   C finish    *********************\n");
	ioMutex.Release();
}

void d()
{
	int j;
	ioMutex.Acquire();
	cout << "\n ************* D Start *********************\n";
	writeToLog("\n ************* D Start *********************\n");
	ioMutex.Release();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "D";
		writeToLog("D");
		ioMutex.Release();
	}

	char r;
	writeToLog("\nHello there! I am D and I WAIT to E\n");
	evDtoE.wait(r);
	writeToLog("Hello there! I am D and E let me go\n");

	writeToLog("Hello there! I am D and I acquire SMARTS.mutexes[2]\n");
	SMARTS.mutexes[2].Acquire();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "D";
		writeToLog("D");
		ioMutex.Release();
	}

	char e;
	writeToLog("\nHello there! I am D and I send to C\n");
	evCtoD.send('C', &e, 0);

	writeToLog("Hello there! I am D and I acquire SMARTS.mutexes[3]\n");
	SMARTS.mutexes[3].Acquire();
	writeToLog("Hello there! I am D and I got SMARTS.mutexes[3]\n");

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "D";
		writeToLog("D");
		ioMutex.Release();
	}

	writeToLog("\nHello there, I am D and I release SMARTS.mutexes[3]\n");
	SMARTS.mutexes[3].Release();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "D";
		writeToLog("D");
		ioMutex.Release();
	}

	//printf("\nCurrent roundtime for D: %d\n", SMARTS.getRoundTime(SMARTS.getCurrentTask()));
	writeToLog("\nHello there, I am D and I release SMARTS.mutexes[2]\n");
	SMARTS.mutexes[2].Release();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "D";
		writeToLog("D");
		ioMutex.Release();
	}

	ioMutex.Acquire();
	cout << "\n *************   D Finish   *********************\n";
	writeToLog("\n *************   D finish    *********************\n");
	ioMutex.Release();
}

void e()
{
	int j;
	ioMutex.Acquire();
	cout << "\n *************   E Start    *********************\n";
	writeToLog("\n *************   E Start    *********************\n");
	ioMutex.Release();
	for (j = 0; j < 5; j++) // Waste 600000 operations time
	{
		for (long i = 0; i < 200000; i++)
			;
		ioMutex.Acquire();
		cout << "E";
		writeToLog("E");
		ioMutex.Release();
	}

	writeToLog("\nHello there, I'm E and I acquire SMARTS.mutexes[3]!\n");
	SMARTS.mutexes[3].Acquire();
	for (j = 0; j < 5; j++) // Waste 600000 operations time
	{
		for (long i = 0; i < 200000; i++)
			;
		ioMutex.Acquire();
		cout << "E";
		writeToLog("E");
		ioMutex.Release();
	}
	writeToLog("\nHello there, I'm E and I send D\n");
	char e;
	evDtoE.send('D', &e, 0);

	for (j = 0; j < 5; j++) // Waste 600000 operations time
	{
		for (long i = 0; i < 200000; i++)
			;
		ioMutex.Acquire();
		cout << "E";
		writeToLog("E");
		ioMutex.Release();
	}

	writeToLog("\nHello there, I'm E and I send F\n");
	evFtoE.send('F', &e, 0);

	for (j = 0; j < 5; j++) // Waste 600000 operations time
	{
		for (long i = 0; i < 200000; i++)
			;
		ioMutex.Acquire();
		cout << "E";
		writeToLog("E");
		ioMutex.Release();
	}

	//printf("\nCurrent roundtime for E: %d\n", SMARTS.getRoundTime(SMARTS.getCurrentTask()));
	writeToLog("\nHello there! I'm E and I release SMARTS.mutexes[3]\n");
	SMARTS.mutexes[3].Release();

	for (j = 0; j < 5; j++) // Waste 600000 operations time
	{
		for (long i = 0; i < 200000; i++)
			;
		ioMutex.Acquire();
		cout << "E";
		writeToLog("E");
		ioMutex.Release();
	}

	ioMutex.Acquire();
	cout << "\n *************   E Finish   *********************\n";
	writeToLog("\n *************   E Finish    *********************\n");
	ioMutex.Release();
}

void f()
{
	//printf("After change: owner: 5, roundTime: %d\n", owner, SMARTS.getRoundTime(5));
	int j;
	ioMutex.Acquire();
	cout << "\n ************* F Start *********************\n";
	writeToLog("\n ************* F Start *********************\n");
	ioMutex.Release();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "F";
		writeToLog("F");
		ioMutex.Release();
	}

	char r;
	writeToLog("\nHello there! I am F and I WAIT to E\n");
	evFtoE.wait(r);
	writeToLog("Hello there! I am F and E let me go\n");

	for (j = 0; j < 20; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "F";
		writeToLog("F");
		ioMutex.Release();
	}

	ioMutex.Acquire();
	//printf("\nCurrent roundtime for F: %d\n", SMARTS.getRoundTime(SMARTS.getCurrentTask()));
	cout << "\n *************   F Finish   *********************\n";
	writeToLog("\n *************   F finish    *********************\n");
	ioMutex.Release();
}

void main()
{
	clrscr();
	clearLog();

	writeToLog("Start\n");
	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, rate_monotonic_scheduling);

	for (int i = 0; i < 4; i++)
		SMARTS.declareMutex(1);

	SMARTS.declareTask(a, 'A', 800, 1); // 5

	SMARTS.declareTask(f, 'F', 810, 1); // 4.5

	SMARTS.declareTask(b, 'B', 820, 1); // 4
	SMARTS.declareTask(c, 'C', 840, 1); // 3
	SMARTS.declareTask(d, 'D', 860, 1); // 2
	SMARTS.declareTask(e, 'E', 880, 1); // 1


	SMARTS.runTheTasks();
	writeToLog("End\n");
}