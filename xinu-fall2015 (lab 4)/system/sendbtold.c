/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	sendbtold(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg,		/* Contents of message		*/
	  int32		maxwait
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptrReceive;		/* Ptr to process' table entry	*/

	if (maxwait < 0) {

		return SYSERR;

	} 

	prptrReceive = &proctab[pid];
	struct	procent *prptrSend = &proctab[currpid];		/* Ptr to process' table entry	*/	
	
	if (prptrReceive->prhasmsg == FALSE) { // process is woken up by receiver

		//send(pid, msg);
		
		mask = disable();
		if (isbadpid(pid)) {
			restore(mask);
			return SYSERR;
		}

		if ((prptrReceive->prstate == PR_FREE) || prptrReceive->prhasmsg) {
			restore(mask);
			return SYSERR;
		}
		prptrReceive->prmsg = msg;		/* Deliver message		*/
		prptrReceive->prhasmsg = TRUE;		/* Indicate message is waiting	*/

		/* If recipient waiting or in timed-wait make it ready */

		if (prptrReceive->prstate == PR_RECV) {
			ready(pid);
		} else if (prptrReceive->prstate == PR_RECTIM) {
			prptrReceive->isSleeping = FALSE;
			unsleep(pid);
			ready(pid);
		}
		restore(mask);		/* Restore interrupts */
		return OK;

	}

	else { // when process is woken up by sleep

		if (maxwait == 0) {

			//prptrReceive = &proctab[pid];
			prptrSend->sndmsg = msg;
			prptrSend->sndflag = TRUE;
			
			prptrSend->prstate = PR_SEND;

		}

		else { // maxwait > 0

			//prptrReceive = &proctab[pid];
			prptrSend->sndmsg = msg;
			prptrSend->sndflag = TRUE;

			insertd(currpid, sleepq, maxwait);
			prptrReceive->isSleeping = TRUE;	

		}
		//kprintf("MESSAGE SENDING: %d\n", currpid);
		myenqueue(currpid, prptrReceive->pq);
		resched();


		if (prptrReceive->prhasmsg == FALSE) { // process woken up by receive
			kprintf("============================================\n");
			 mask = disable();

			prptrReceive->prmsg = msg;		/* Deliver message		*/
			prptrReceive->prhasmsg = TRUE;		/* Indicate message is waiting	*/

			/* If recipient waiting or in timed-wait make it ready */

			if (prptrReceive->prstate == PR_RECV) {
				ready(pid);
			} else if (prptrReceive->prstate == PR_RECTIM) {
				prptrReceive->isSleeping = FALSE;
				unsleep(pid);
				ready(pid);
			}

			restore(mask);		/* Restore interrupts */
			return OK;

		} else { // woken up by sleep

//			mydequeue(prptrReceive->pq);
			mygetitem(currpid);
			prptrSend->sndflag = FALSE;
			restore(mask);		/* Restore interrupts */
			return TIMEOUT;
		}
		// process wakes up after resched();

		// check if process is being woken up from sleep queue or receiving queue
		// if receiving queue then can deliver message
		// if woken by sleep queue then should SYSERR

		// have to remove process from other queues (if receive then remove from sleep queue)

		// if hasmsg flag is false then process was woken by receive
	} 

	/*mask = disable();
	
	prptr->prmsg = msg;		
	prptr->prhasmsg = TRUE;		


	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		prptr->isSleeping = FALSE;
		unsleep(pid);
		ready(pid);
	}
	restore(mask);	

	return OK;*/

}