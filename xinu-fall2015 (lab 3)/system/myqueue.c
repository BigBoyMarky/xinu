/* queue.c - enqueue, dequeue */

#include <xinu.h>

struct qentry	myqueuetab[myNQENT];	/* Table of process queues	*/

/*------------------------------------------------------------------------
 *  enqueue  -  Insert a process at the tail of a queue
 *------------------------------------------------------------------------
 */
pid32	myenqueue(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q		/* ID of queue to use		*/
	)
{
	int	tail, prev;		/* Tail & previous node indexes	*/

	if (myisbadqid(q) || myisbadpid(pid)) {
		return SYSERR;
	}

	tail = myqueuetail(q);
	prev = myqueuetab[tail].qprev;

	myqueuetab[pid].qnext  = tail;	/* Insert just before tail node	*/
	myqueuetab[pid].qprev  = prev;
	myqueuetab[prev].qnext = pid;
	myqueuetab[tail].qprev = pid;
	return pid;
}

/*------------------------------------------------------------------------
 *  dequeue  -  Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
pid32	mydequeue(
	  qid16		q		/* ID queue to use		*/
	)
{
	pid32	pid;			/* ID of process removed	*/

	if (myisbadqid(q)) {
		return SYSERR;
	} else if (myisempty(q)) {
		return EMPTY;
	}

	pid = mygetfirst(q);
	myqueuetab[pid].qprev = EMPTY;
	myqueuetab[pid].qnext = EMPTY;
	return pid;
}
