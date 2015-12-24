/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	kprintf("\n\nRESCHEDLING =====\n\n");

	if (ptold->prclassify == 0) {
		kprintf("\n\nA\n\n");
		ptold->prprio = tsdtab[ptold->prprio].ts_slpret;
	} else {
		kprintf("\n\nB\n\n");
		ptold->prprio = tsdtab[ptold->prprio].ts_tqexp;
	}

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		//if (ptold->prprio > firstkey(readylist)) {
		kprintf("\n\nC    %d\n\n", currpid);
		if (ptold->prprio > firstkey(mlqtable[ptold->prprio].queuetable) && currpid != 0) {
			kprintf("\n\nD\n\n");
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		//insert(currpid, readylist, ptold->prprio);
		//mlqenqueue(currpid, mlqtable[ptold->prprio].queuetable);
		insert(currpid, mlqtable[ptold->prprio].queuetable, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	//currpid = dequeue(readylist);
	//int temp = dequeue(readylist);
	//int temp = mlqdequeue(readylist);
	int temp = mlqdequeue(mlqtable[ptold->prprio].queuetable);
	kprintf("\n\nTEMP PID: %d\n\n", temp);
	if (temp == 0) {
	//	enqueue(temp, readylist);
		//mlqenqueue(temp, readylist);
		kprintf("IN RESCHED DEQUEUEING\n");
		//mlqenqueue(temp, mlqtable[ptold->prprio].queuetable);
		insert(currpid, mlqtable[ptold->prprio].queuetable, ptold->prprio);
	//	currpid = dequeue(readylist);
		//currpid = mlqdequeue(readylist);
		currpid = mlqdequeue(mlqtable[ptold->prprio].queuetable);
	} else {
		currpid = temp;
	}

	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	//preempt = tsdtab[ptnew->prprio].ts_quantum;
	kprintf("\n\nCONTEXT SWITCHING   %d\n\n", currpid);

	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
