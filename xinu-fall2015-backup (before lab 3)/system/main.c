/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

int myvictimglobal = 0;

process	main(void)
{

	// I moved all of the code from previous labs to another file called prevCode
	// so that main.c is much more readable


	kprintf("\n================================================================\n");
	kprintf("\nThis is the start of Main\n");
	kprintf("\n================================================================\n\n");

/*	kprintf("Lab 2 Problem 3:\n\n");
	int myvictimID = create(myvictim, 4096, 20, "myvictim", 1, NULL);
	resume(myvictimID);
	int myattackerID = create(myattacker, 4096, 20, "myattacker", 1, NULL);
	resume(myattackerID);

	kprintf("\n\n\nProblem 4 in Lab2Answers.pdf\n\nProblem 5:\n\n");
*/
	// this is all of the test cases for problem 5 to view them just uncomment them and comment out problem 3

	int cpuintensiveA = create(cpuintensive, 1024, 1, "cpuintensiveA", 0);
	int cpuintensiveB = create(cpuintensive, 1024, 1, "cpuintensiveB", 0);
	int cpuintensiveC = create(cpuintensive, 1024, 1, "cpuintensiveC", 0);
	int cpuintensiveD = create(cpuintensive, 1024, 1, "cpuintensiveD", 0);

	/*int iointensiveA = create(iointensive, 1024, 1, "iointensiveA", 0);
	int iointensiveB = create(iointensive, 1024, 1, "iointensiveB", 0);
	int iointensiveC = create(iointensive, 1024, 1, "iointensiveC", 0);
	int iointensiveD = create(iointensive, 1024, 1, "iointensiveD", 0);
*/
	resume(cpuintensiveA);
	resume(cpuintensiveB);
	resume(cpuintensiveC);
	resume(cpuintensiveD);

/*	resume(iointensiveA);
	resume(iointensiveB);
	resume(iointensiveC);
	resume(iointensiveD);*/

	/*struct procent *A = &proctab[cpuintensiveA];
	struct procent *B = &proctab[cpuintensiveB];
	struct procent *C = &proctab[cpuintensiveC];
	struct procent *D = &proctab[cpuintensiveD];
	kprintf("\n=======================================\n%d", A->prcpuused);

			kprintf("\n=======================================\n%d", B->prcpuused);

kprintf("\n=======================================\n%d", C->prcpuused);

kprintf("\n=======================================\n%d", D->prcpuused);
*/


	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}

	return OK;
}
