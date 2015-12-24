/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receiveold(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {//kprintf("pre resched()\n");
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}//kprintf("post resched()\n");
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/

	if (mynonempty(prptr->pq)) {
		
		pid32 mypid = mydequeue(prptr->pq); 

		//kprintf("DEQUEUED: %d\n", mypid);

		struct procent *mypidptr = &proctab[mypid];

		if (mypidptr->prstate == PR_SEND) {
			
			if (mypidptr->isSleeping) {// if (mypidptr->prstate != PR_RECTIM) {
		//				kprintf("UNSLEEPING: %d\n", mypid);
						mypidptr->isSleeping = FALSE;
						unsleep(mypid);
						ready(mypid);

			} else {
		//		kprintf("SETTING READY: %d\n", mypid);

				ready(mypid);
			}
		} 
		//kprintf("DONE WITH IF STATEMENT\n");
	}

	//kprintf("AFTER MYNONEMPTY \n");

	restore(mask);
	return msg;
}
