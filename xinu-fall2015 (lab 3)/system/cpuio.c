#include <xinu.h>

void cpuio() {

	//kprintf("CURRPID: %d\n", currpid);
	struct procent *proc = &proctab[currpid];
//kprintf("PREEMPT: %d\n", preempt);
	if (proc->prclassify == 1) {
		if (currpid == 0)
			proc->prprio = 0;
		else 
			proc->prprio = tsdtab[proc->prprio].ts_tqexp;
	}
	else {
		if (currpid == 0)
			proc->prprio = 0;
		else 
			proc->prprio = tsdtab[proc->prprio].ts_slpret;
	}/*
	if (preempt <= 0) { //CPU
	//	if (currpid != 0)
		if (currpid == 0)
			proc->prprio = 0;
		else
			proc->prprio = tsdtab[proc->prprio].ts_tqexp;
	} else {
	//	if (currpid != 0)
		if (currpid == 0)
			proc->prprio = 0;
		else
			proc->prprio = tsdtab[proc->prprio].ts_slpret;
	}*/


	//kprintf("PRPRIO: %d     %d\n", proc->prprio, currpid);
	//preempt = tsdtab[proc->prprio].ts_quantum;		/* Reset time slice for process	*/

}
