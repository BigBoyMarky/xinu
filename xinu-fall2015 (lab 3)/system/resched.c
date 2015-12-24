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
/*
	int i;
	int j;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < NPROC; j++) {
			if (mlqtable[i][j].processID != EMPTY)
				kprintf("%d  %d\n", mlqtable[i][j].processID, j);
		}
	}*/
//kprintf("RESCHEDULING\n");
	/* If rescheduling is deferred, record attempt and return */
//kprintf("CCURRPID: %d", currpid);
	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
//		kprintf("DEFFERED");
	}

	/* Point to process table entry for the current (old) process */
	ptold = &proctab[currpid];

	/*if (preempt <= 0) { //CPU
		ptold->prprio = tsdtab[ptold->prprio].ts_tqexp;
	} else {
		ptold->prprio = tsdtab[ptold->prprio].ts_slpret;
	}*/

	/*if (ptold->prclassify == 0) {
		ptold->prprio = tsdtab[ptold->prprio].ts_slpret;
	} else {
		ptold->prprio = tsdtab[ptold->prprio].ts_tqexp;
	}*/
	//kprintf("CURRPID: %d   %d\n", currpid, ptold->prstate);
	//kprintf("PRIORITY: %d   %d\n", ptold->prprio, currpid);
	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		//timestamp = clktimefine;
			//	kprintf("CURRPIDDD: %d", currpid);
			//kprintf("CURRPID: %d", currpid);
		//if (ptold->prprio > firstkey(readylist)) {
//		if (ptold->prprio > mlqprioritypeek()) {
	//		kprintf("CURRPID RETURN: %d", currpid);
			//kprintf("PEEKING %d    %d\n", ptold->prprio, mlqprioritypeek());
//			return;
//		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		//ptold->prcpuused += clktimefine - timestamp;
		//insert(currpid, readylist, ptold->prprio);
		//kprintf("ENQUEUED CURRPID: %d\n", currpid);
		mlqenqueue(currpid);
	}

	//ptold->prcpuused += clktimefine - timestamp;


	/* Force context switch to highest priority ready process */
	//currpid = dequeue(readylist);

	currpid = mlqdequeue();
	//kprintf("DEQUEUED CURRPID: %d\n", currpid);


	if (currpid == 0) {
		mlqenqueue(currpid);
		currpid = mlqdequeue();

	}

	ptnew = &proctab[currpid];

	ptnew->prstate = PR_CURR;
	preempt = tsdtab[ptnew->prprio].ts_quantum;		/* Reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	//timestamp = clktimefine;

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
