/* sleep.c - sleep sleepms */

#include <xinu.h>

#define	MAXSECONDS	4294967		/* Max seconds per 32-bit msec	*/

/*------------------------------------------------------------------------
 *  sleep  -  Delay the calling process n seconds
 *------------------------------------------------------------------------
 */
syscall	sleep(
	  uint32	delay		/* Time to delay in seconds	*/
	)
{
	if (delay > MAXSECONDS) {
		return SYSERR;
	}
	sleepms(1000*delay);
	return OK;
}

/*------------------------------------------------------------------------
 *  sleepms  -  Delay the calling process n milliseconds
 *------------------------------------------------------------------------
 */
syscall	sleepms(
	  uint32	delay		/* Time to delay in msec.	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/

	mask = disable();
	if (delay == 0) {
		yield();
		restore(mask);
		return OK;
	}

	/* Delay calling process */

	if (insertd(currpid, sleepq, delay) == SYSERR) {
		restore(mask);
		return SYSERR;
	}

	/*struct procent *proc = &proctab[currpid];
	if (preempt <= 0) { //CPU
		proc->prprio = tsdtab[proc->prprio].ts_tqexp;
	} else {
		proc->prprio = tsdtab[proc->prprio].ts_slpret;
	}
	preempt = tsdtab[proc->prprio].ts_quantum;*/
	struct procent *proc = &proctab[currpid];
	proc->prclassify = 0;
	proctab[currpid].prstate = PR_SLEEP;
	//preempt = tsdtab[proctab[currpid]->prprio].ts_quantum;
	cpuio();
	resched();
	restore(mask);
	return OK;
}


//io