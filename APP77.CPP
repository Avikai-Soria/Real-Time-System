/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory            */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum              */
/* Jerusalem College of Technology, 5759-64 (1999-03)               */
/* update  Tishrey   5777                                           */
/* APP77.CPP, an application to demonstrate SMARTS77  functioning   */
/********************************************************************/

#include "smarts77.h"

Mutex ioMutex(0);
Mutex aMutex(1);
Mutex bMutex(1);
Event evCtoA, evEtoA;
Event evFtoB, evDtoB;

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

	writeToLog("Hello there! I am A and I acquire aMutex\n");
	aMutex.Acquire();

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "A";
		writeToLog("A");
		ioMutex.Release();
	}
	char d;
	writeToLog("Hello there! I am A and I send to C \n");
	evCtoA.send('C', &d, 0);
	writeToLog("Hello there! I am A and I send to E \n");
	evEtoA.send('E', &d, 0);
	writeToLog("Hello there! I am A and I continue running after events");

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "A";
		writeToLog("A");
		ioMutex.Release();
	}

	writeToLog("Hello there! I am A and I release aMutex\n");
	aMutex.Release();

	writeToLog("Amutex was released.\n");
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

	char r;
	writeToLog("Hello there! I am E and I WAIT to A\n");
	evEtoA.wait(r);
	writeToLog("Hello there! I am E and A let me go\n");
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

void c()
{
	int j;
	ioMutex.Acquire();
	cout << "\n *************   C Start    *********************\n";
	writeToLog("\n *************   C Start    *********************\n");
	ioMutex.Release();
	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 600000 operations time
		ioMutex.Acquire();
		cout << "C";
		writeToLog("C");
		ioMutex.Release();
	}
	char r;
	writeToLog("Hello there! I am C and I WAIT to A\n");
	evCtoA.wait(r);
	writeToLog("Hello there! I am C and A let me go\n");

	writeToLog("Hello there! I am C and and I wait to aMutex\n");
	aMutex.Acquire();
	writeToLog("Hello there! I am C and I continue, acquired aMutex\n");

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 600000 operations time
		ioMutex.Acquire();
		cout << "C";
		writeToLog("C");
		ioMutex.Release();
	}

	writeToLog("Hello there, C release Amutex");
	aMutex.Release();
	writeToLog("Hello there! I'm C and I release aMutex!\n");
	ioMutex.Acquire();
	cout << "\n *************   C Finish   *********************\n";
	writeToLog("\n *************   C Finish    *********************\n");
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

	writeToLog("Hello there! I am B and I acquire bMutex\n");
	bMutex.Acquire();

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
	writeToLog("Hello there! I am B and I send to D \n");
	evDtoB.send('D', &d, 0);
	writeToLog("Hello there! I am B and I send to F \n");
	evFtoB.send('F', &d, 0);
	writeToLog("Hello there! I am B and I continue running after events\n");

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "B";
		writeToLog("B");
		ioMutex.Release();
	}

	writeToLog("Hello there! I am B and I release bMutex\n");
	bMutex.Release();
	writeToLog("Hello there! I am B and bMutex was released\n");

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

void f()
{
	int j;
	ioMutex.Acquire();
	cout << "\n *************   F Start    *********************\n";
	writeToLog("\n *************   F Start    *********************\n");
	ioMutex.Release();
	for (j = 0; j < 5; j++) // Waste 600000 operations time
	{
		for (long i = 0; i < 200000; i++)
			;
		ioMutex.Acquire();
		cout << "F";
		writeToLog("F");
		ioMutex.Release();
	}

	char r;
	writeToLog("Hello there! I am F and I WAIT to B\n");
	evFtoB.wait(r);
	writeToLog("Hello there! I am F and B let me go\n");
	for (j = 0; j < 5; j++) // Waste 600000 operations time
	{
		for (long i = 0; i < 200000; i++)
			;
		ioMutex.Acquire();
		cout << "F";
		writeToLog("F");
		ioMutex.Release();
	}

	ioMutex.Acquire();
	cout << "\n *************   F Finish   *********************\n";
	writeToLog("\n *************   F Finish    *********************\n");
	ioMutex.Release();
}

void d()
{
	int j;
	ioMutex.Acquire();
	cout << "\n *************   D Start    *********************\n";
	writeToLog("\n *************   D Start    *********************\n");
	ioMutex.Release();
	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 600000 operations time
		ioMutex.Acquire();
		cout << "D";
		writeToLog("D");
		ioMutex.Release();
	}
	char r;
	writeToLog("Hello there! I am D and I WAIT to B\n");
	evDtoB.wait(r);
	writeToLog("Hello there! I am D and B let me go\n");

	writeToLog("Hello there! I am D and and I wait to bMutex\n");
	bMutex.Acquire();
	writeToLog("Hello there! I am D and B let me go\n");

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 600000 operations time
		ioMutex.Acquire();
		cout << "D";
		writeToLog("D");
		ioMutex.Release();
	}

	bMutex.Release();
	writeToLog("Hello there! I'm D and I release bMutex!\n");
	ioMutex.Acquire();
	cout << "\n *************   D Finish   *********************\n";
	writeToLog("\n *************   D Finish    *********************\n");
	ioMutex.Release();
}

void main()
{
	clrscr();
	writeToLog("Start\n");
	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, rate_monotonic_scheduling);
	SMARTS.declareTask(a, 'A', 412, 1); // L
	SMARTS.declareTask(e, 'E', 407, 1); // M
	SMARTS.declareTask(c, 'C', 402, 1); // H

	SMARTS.declareTask(b, 'B', 410, 1); // L
	SMARTS.declareTask(f, 'F', 405, 1); // M
	SMARTS.declareTask(d, 'D', 400, 1); // H

	SMARTS.runTheTasks();
	writeToLog("End\n");
}