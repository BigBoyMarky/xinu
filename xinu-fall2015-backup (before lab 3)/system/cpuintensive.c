#include <xinu.h>

void cpuintensive() {

	int i;
	int j;
	int loop1 = 10;
	int loop2 = 1000000;

	const char source[52] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
	char destination[52];

	struct procent *proc = &proctab[currpid];

	kprintf("\n\n");

	for (i = 0; i < loop1; i++) {

//		memcpy(destination, source, strlen(source) + 1);

		for (j = 0; j < loop2; j++) {

			memcpy(destination, source, strlen(source) + 1);

		}

		kprintf("PID: %d Outer Loop: %d Priority: %d Remaining Time Slice: %d\n", currpid, i, proc->prprio, preempt);

	}

	kprintf("CPU CPU time used: %d\n", proc->prcpuused);
}
