/* queue.c - enqueue, dequeue */

#include <xinu.h>

struct qentry	alrmmyqueuetab[alrmmyNQENT];	/* Table of process queues	*/

/*------------------------------------------------------------------------
 *  enqueue  -  Insert a process at the tail of a queue
 *------------------------------------------------------------------------
 */
pid32	alrmmyenqueue(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q		/* ID of queue to use		*/
	)
{
	int	tail, prev;		/* Tail & previous node indexes	*/

	if (alrmmyisbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	tail = alrmmyqueuetail(q);
	prev = alrmmyqueuetab[tail].qprev;

	alrmmyqueuetab[pid].qnext  = tail;	/* Insert just before tail node	*/
	alrmmyqueuetab[pid].qprev  = prev;
	alrmmyqueuetab[prev].qnext = pid;
	alrmmyqueuetab[tail].qprev = pid;
	return pid;
}

/*------------------------------------------------------------------------
 *  dequeue  -  Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
pid32	alrmmydequeue(
	  qid16		q		/* ID queue to use		*/
	)
{
	pid32	pid;			/* ID of process removed	*/

	if (alrmmyisbadqid(q)) {
		return SYSERR;
	} else if (alrmmyisempty(q)) {
		return EMPTY;
	}

	pid = alrmmygetfirst(q);
	alrmmyqueuetab[pid].qprev = EMPTY;
	alrmmyqueuetab[pid].qnext = EMPTY;
	return pid;
}
