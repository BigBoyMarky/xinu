/* newqueue.c - newqueue */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  newqueue  -  Allocate and initialize a queue in the global queue table
 *------------------------------------------------------------------------
 */
qid16	mynewqueue(void)
{
	static qid16	nextqid=NPROC;	/* Next list in queuetab to use	*/
	qid16		q;		/* ID of allocated queue 	*/

	q = nextqid;
	if (q > myNQENT) {		/* Check for table overflow	*/
		return SYSERR;
	}

	nextqid += 2;			/* Increment index for next call*/

	/* Initialize head and tail nodes to form an empty queue */

	myqueuetab[myqueuehead(q)].qnext = myqueuetail(q);
	myqueuetab[myqueuehead(q)].qprev = EMPTY;
	myqueuetab[myqueuehead(q)].qkey  = MAXKEY;
	myqueuetab[myqueuetail(q)].qnext = EMPTY;
	myqueuetab[myqueuetail(q)].qprev = myqueuehead(q);
	myqueuetab[myqueuetail(q)].qkey  = MINKEY;
	return q;
}
