/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	//insert(pid, readylist, prptr->prprio);
	//kprintf("READY: %d\n\n\n", pid);

	prptr->prclassify = 1;
	//kprintf("QUEITING: %d\n", pid);
	cpuio();
	//kprintf("READY ENQUEUE: %d\n", pid);
	mlqenqueue(pid);
	resched();

	return OK;
}
