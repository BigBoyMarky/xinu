/* sendbt.c - sendbt */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  sendbt  -  Pass a message to a process and start recipient if waiting.
 *  has an addition field maxwait for the max amount of time a blocked
 *  message can wait before being dropped
 *------------------------------------------------------------------------
 */
syscall	sendbt(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg,		/* Contents of message		*/
	  int32		maxwait
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptrReceiver;		/* Ptr to process' table entry	*/
	struct	procent *prptrSender;

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptrReceiver = &proctab[pid];
	prptrSender = &proctab[currpid];
	if (prptrReceiver->prstate == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (prptrReceiver->prhasmsg == TRUE) { // handling blocking of messages
										   // the receiver already has a message so need 
										   // to insert the message into the process' queue

		prptrSender->sndmsg = msg;
		prptrSender->sndflag = TRUE;

		if (maxwait > 0) { // if maxwait > 0, then the sending process is inserted into the sleep queue
						   // which is then to be woken up after maxwait time has been reached
			prptrSender->isSleeping = TRUE;
			insertd(currpid, sleepq, maxwait);
			//kprintf("PID:%d TIME:%d\n", currpid, clktimefine);
		}

		myenqueue(currpid, prptrReceiver->pq);
		prptrSender->prstate = PR_SEND;
		resched();

		if (prptrReceiver->prhasmsg == TRUE) { // process was woken up by sleep
											   // drop the message since time is up
			mygetitem(currpid);
			restore(mask);
			return TIMEOUT;
		}

	}

	prptrReceiver->prmsg = msg;		/* Deliver message		*/
	prptrReceiver->prhasmsg = TRUE;		/* Indicate message is waiting	*/

	/* If recipient waiting or in timed-wait make it ready */

	if (prptrReceiver->prstate == PR_RECV) {
		ready(pid);
	} else if (prptrReceiver->prstate == PR_RECTIM) {
		prptrSender->isSleeping = FALSE; // set the sleeping flag to false since removing it from sleepq
		unsleep(pid);
		ready(pid);
	}
	restore(mask);		/* Restore interrupts */
	return OK;
}
