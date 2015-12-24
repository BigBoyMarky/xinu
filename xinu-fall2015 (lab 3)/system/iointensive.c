#include <xinu.h>

void iointensive() {

	int i;
	int j;
	int loop1 = 10;
	int loop2 = 1000;

	struct procent *proc = &proctab[currpid];

	//kprintf("iointensive\n\n");

	for (i = 0; i < loop1; i++) {

		for (j = 0; j < loop2; j++) {

			sleepms(10);

		}

		kprintf("IO PID: %d Outer Loop: %d Priority: %d Remaining Time Slice: %d\n", currpid, i, proc->prprio, preempt);

	}

	//kprintf("IO CPU time used: %d\n", proc->prcpuused);

	kprintf("DONE WITH IO INTENSIVE\n");
}
