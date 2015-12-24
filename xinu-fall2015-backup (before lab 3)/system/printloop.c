#include <xinu.h>

void printloop(char val) {

//	while (true) {

	int i = 0;
	int j;
	int OUTERB = 5;
	int INNERB = 100000000;

	for (; i < OUTERB; i++) {

		kprintf("%c", val);

		for (j = 0; j < INNERB; j++) {

		}

	}

/*	struct procent *proc = &proctab[currpid];
	int time = proc->prcpuused;
	kprintf("\nTIME IN PRINTLOOP: %d\n", time);*/
}
