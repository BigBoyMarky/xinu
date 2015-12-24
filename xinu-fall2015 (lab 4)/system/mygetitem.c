/* getitem.c - getfirst, getlast, getitem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getfirst  -  Remove a process from the front of a queue
 *------------------------------------------------------------------------
 */
pid32	mygetfirst(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32	head;

	if (myisempty(q)) {
		return EMPTY;
	}

	head = myqueuehead(q);
	return mygetitem(myqueuetab[head].qnext);
}

/*------------------------------------------------------------------------
 *  getlast  -  Remove a process from end of queue
 *------------------------------------------------------------------------
 */
pid32	mygetlast(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32 tail;

	if (myisempty(q)) {
		return EMPTY;
	}

	tail = myqueuetail(q);
	return mygetitem(myqueuetab[tail].qprev);
}

/*------------------------------------------------------------------------
 *  getitem  -  Remove a process from an arbitrary point in a queue
 *------------------------------------------------------------------------
 */
pid32	mygetitem(
	  pid32		pid		/* ID of process to remove	*/
	)
{
	pid32	prev, next;

	next = myqueuetab[pid].qnext;	/* Following node in list	*/
	prev = myqueuetab[pid].qprev;	/* Previous node in list	*/
	myqueuetab[prev].qnext = next;
	myqueuetab[next].qprev = prev;
	return pid;
}
