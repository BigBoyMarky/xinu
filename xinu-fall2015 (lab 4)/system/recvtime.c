/* recvtime.c - recvtime */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  recvtime  -  Wait specified time to receive a message and return
 *------------------------------------------------------------------------
 */
umsg32	recvtime(
	  int32		maxwait		/* Ticks to wait before timeout */
        )
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent	*prptr;		/* Tbl entry of current process	*/
	umsg32	msg;			/* Message to return		*/
	pid32 unblocked;

	if (maxwait < 0) {
		return SYSERR;
	}
	mask = disable();

	/* Schedule wakeup and place process in timed-receive state */

	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {	/* If message waiting, no delay	*/
		if (insertd(currpid,sleepq,maxwait) == SYSERR) {
			restore(mask);
			return SYSERR;
		}
		prptr->prstate = PR_RECTIM;
		resched();
	}

	/* Either message arrived or timer expired */

	if (prptr->prhasmsg) {
		msg = prptr->prmsg;	/* Retrieve message		*/
		prptr->prhasmsg = FALSE;/* Reset message indicator	*/
	} else {
		msg = TIMEOUT;
	}

	if (mynonempty(prptr->pq)) {
		unblocked = mydequeue(prptr->pq);
		struct procent *prptrUnblocked = &proctab[unblocked];
		//When the receiver buffer eventually clears and the blocked process succeeds in
		//sending a message before the maxwait sleep expires, the process must be removed from the sleep queue.
		if (prptrUnblocked->isSleeping) {
			prptrUnblocked->isSleeping = FALSE;
			unsleep(unblocked);
		}
		ready(unblocked);
	}

	restore(mask);
	return msg;
}