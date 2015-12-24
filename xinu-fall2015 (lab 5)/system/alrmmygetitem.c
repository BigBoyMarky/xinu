/* getitem.c - getfirst, getlast, getitem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getfirst  -  Remove a process from the front of a queue
 *------------------------------------------------------------------------
 */
pid32	alrmmygetfirst(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32	head;

	if (alrmmyisempty(q)) {
		return EMPTY;
	}

	head = alrmmyqueuehead(q);
	return alrmmygetitem(alrmmyqueuetab[head].qnext);
}

/*------------------------------------------------------------------------
 *  getlast  -  Remove a process from end of queue
 *------------------------------------------------------------------------
 */
pid32	alrmmygetlast(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32 tail;

	if (alrmmyisempty(q)) {
		return EMPTY;
	}

	tail = alrmmyqueuetail(q);
	return alrmmygetitem(alrmmyqueuetab[tail].qprev);
}

/*------------------------------------------------------------------------
 *  getitem  -  Remove a process from an arbitrary point in a queue
 *------------------------------------------------------------------------
 */
pid32	alrmmygetitem(
	  pid32		pid		/* ID of process to remove	*/
	)
{
	pid32	prev, next;

	next = alrmmyqueuetab[pid].qnext;	/* Following node in list	*/
	prev = alrmmyqueuetab[pid].qprev;	/* Previous node in list	*/
	alrmmyqueuetab[prev].qnext = next;
	alrmmyqueuetab[next].qprev = prev;
	return pid;
}
