/* recvclr.c - recvclr */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  recvclr  -  Clear incoming message, and return message if one waiting
 *------------------------------------------------------------------------
 */
umsg32	recvclr(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/
	pid32 unblocked;

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == TRUE) {
		msg = prptr->prmsg;	/* Retrieve message		*/
		prptr->prhasmsg = FALSE;/* Reset message flag		*/
	} else {
		msg = OK;
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