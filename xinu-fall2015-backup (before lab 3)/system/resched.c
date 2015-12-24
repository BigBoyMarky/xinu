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

	struct procent *ptnull;
	ptnull = &proctab[NULLPROC];

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];
//kprintf("RESCHED   %d\n", currpid);
	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prcpuused < firstkey(readylist)) {
			ptold->prcpuused += clktimefine - timestamp;
			timestamp = clktimefine;
			//ptold->prprio = 1000 / ptold->prcpuused;
			/*if (ptold->prprio < ptnew->prprio)
				ptnull->prprio = ptold->prprio - 1;
			else
				ptnull->prprio = ptnew->prprio - 1;*/
			ptnull->prcpuused = ptold->prcpuused + 1;
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		ptold->prcpuused += clktimefine - timestamp;
		//ptold->prprio = 1000 / ptold->prcpuused;
		//insert(currpid, readylist, ptold->prprio);
		insertNonDescending(currpid, readylist, ptold->prcpuused);
	} else {
		ptold->prcpuused += clktimefine - timestamp;
		//ptold->prprio = 1000 / ptold->prcpuused;
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);
	timestamp = clktimefine;
//	ptold->prcpuused += clktimefine - timestamp;
	/* Old process returns here when resumed */

	/*if (ptold->prprio < ptnew->prprio)
		ptnull->prprio = ptold->prprio - 1;
	else
		ptnull->prprio = ptnew->prprio - 1;*/
	ptnull->prcpuused = ptold->prcpuused + 1;
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
