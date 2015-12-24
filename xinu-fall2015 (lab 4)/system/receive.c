/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/
	pid32 unblocked;

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}//kprintf("RECEIVE RESETTING THE MESSAGES \n");
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/

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
