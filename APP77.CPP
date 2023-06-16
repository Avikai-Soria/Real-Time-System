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

Event evCtoA,evCtoB;// user Functions
void a()
{
	int j;
	ioMutex.Acquire();
	cout << "\n *************   A Start    *********************\n";
	ioMutex.Release();
	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "A";
		ioMutex.Release();
	}
    x<<cin;
	char d;=
	 evCtoA.wait(d);
	for (j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 200000 operations time
		ioMutex.Acquire();
		cout << "A";
		ioMutex.Release();
	}
    aMutex.Acquire();
	Mutex.Acquire();
	cout << "\n *************   A Finish   *********************\n";
	ioMutex.Release();
}

void b()
{
	ioMutex.Acquire();
	cout << "\n *************   B Start    *********************\n";
	ioMutex.Release();
	for (int j = 0; j < 5; j++) // Waste 600000 operations time
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
}

void c()
{
	ioMutex.Acquire();
	cout << "\n *************   C Start    *********************\n";
	ioMutex.Release();
	for (int j = 0; j < 5; j++)
	{
		for (long i = 0; i < 200000; i++)
			; // Waste 600000 operations time
		ioMutex.Acquire();
		cout << "C";
		ioMutex.Release();
	}
	ioMutex.Acquire();
	cout << "\n *************   C Finish   *********************\n";
	ioMutex.Release();
}

void main()
{
	clrscr();
	FILE *f = fopen("filename.txt", "a");  //a  == append

	fprintf(f,"text to print");

	fclose(f);

	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, rate_monotonic_scheduling);
	SMARTS.declareTask(a, 'A', 400, 3);
	SMARTS.declareTask(b, 'B', 401, 3);
	SMARTS.declareTask(c, 'C', 402, 3);
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