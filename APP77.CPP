/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory            */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum              */
/* Jerusalem College of Technology, 5759-64 (1999-03)               */
/* update  Tishrey   5777                                           */
/* APP77.CPP, an application to demonstrate SMARTS77  functioning   */
/********************************************************************/


#include "smarts77.h"

Mutex ioMutex;
Mutex aMutex;
Mutex bMutex;
Event evCtoA,evBtoA;// user Functions

void writeToLog(char *str)
{
	FILE *f = fopen("log.txt", "a");  //a  == append
	fprintf(f, str);
	fclose(f);
}

// user Functions
void a()
{
	writeToLog( "\n *************   A Start    *********************\n");
	int j;
	ioMutex.Acquire();
	cout << "\n *************   A Start    *********************\n";
	ioMutex.Release();
	for ( j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "A";
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
		ioMutex.Release();
	}
	char d;
	writeToLog("Hello there! I am A and I send to C \n");
	evCtoA.send('C',&d,0);
	writeToLog("Hello there! I am A and I send to B \n");
	evBtoA.send('B',&d,0);

	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "A";
		ioMutex.Release();
	}

	writeToLog("Hello there! I am A and I release aMutex\n");
	aMutex.Release();

	ioMutex.Acquire();
	cout << "\n *************   A Finish   *********************\n";
	ioMutex.Release();
	writeToLog( "\n *************   A finish    *********************\n");

}

void b()
{
	int j;
	writeToLog( "\n *************   B Start    *********************\n");
	ioMutex.Acquire();
	cout << "\n *************   B Start    *********************\n";
	ioMutex.Release();
	for (j = 0; j < 5; j++) // Waste 600000 operations time
	{
		for (long i = 0; i < 200000; i++)
			;
		ioMutex.Acquire();
		cout << "B";
		ioMutex.Release();
	}

	char r;
	writeToLog("Hello there! I am B and I WAIT to A\n");
	evBtoA.wait(r);
	writeToLog("Hello there! I am B and A let me go\n");
	for ( j = 0; j < 5; j++) // Waste 600000 operations time
	{
		for (long i = 0; i < 200000; i++)
			;
		ioMutex.Acquire();
		cout << "B";
		ioMutex.Release();
	}

	ioMutex.Acquire();
	cout << "\n *************   B Finish   *********************\n";
	ioMutex.Release();
	writeToLog( "\n *************   B Finish    *********************\n");
}

void c()
{
	int j;
	writeToLog( "\n *************   C Start    *********************\n");
	ioMutex.Acquire();
	cout << "\n *************   C Start    *********************\n";
	ioMutex.Release();
	for ( j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 600000 operations time
		ioMutex.Acquire();
		cout << "C";
		ioMutex.Release();
	}
	char r;
	writeToLog("Hello there! I am C and I WAIT to A\n");
	evCtoA.wait(r);
	writeToLog("Hello there! I am C and A let me go\n");

	writeToLog("Hello there! I am C and and I wait to aMutex\n");
	aMutex.Acquire();

	for ( j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 600000 operations time
		ioMutex.Acquire();
		cout << "C";
		ioMutex.Release();
	}

	aMutex.Release();
	ioMutex.Acquire();
	cout << "\n *************   C Finish   *********************\n";
	ioMutex.Release();
	writeToLog( "\n *************   C Finish    *********************\n");
}

void main()
{
	clrscr();
	writeToLog("Start\n");
	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, rate_monotonic_scheduling);
	SMARTS.declareTask(a, 'A', 402, 1);
	SMARTS.declareTask(b, 'B', 401, 1);
	SMARTS.declareTask(c, 'C', 400, 1);
	SMARTS.runTheTasks();
	writeToLog("End\n");
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

/*
RMS Succeed:
	SMARTS.declareTask(a, 'A', 112, 1);
	SMARTS.declareTask(b, 'B', 224, 2);
	SMARTS.declareTask(c, 'C', 448, 3);

*/
/*
	Queue q;

	// Inserting elements in Circular Queue
	q.enQueue(14);
	q.enQueue(22);
	q.enQueue(13);
	q.enQueue(-6);

	// Display elements present in Circular Queue
	q.displayQueue();

	// Deleting elements from Circular Queue
	printf("\nDeleted value = %d", q.deQueue());
	printf("\nDeleted value = %d", q.deQueue());

	q.displayQueue();

	q.enQueue(9);
	q.enQueue(20);
	q.enQueue(5);

	q.displayQueue();

	q.enQueue(20);
*/