/* newqueue.c - newqueue */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  newqueue  -  Allocate and initialize a queue in the global queue table
 *------------------------------------------------------------------------
 */
qid16	newqueue(void)
{
	static qid16	nextqid=NPROC;	/* Next list in queuetab to use	*/
	qid16		q;		/* ID of allocated queue 	*/

	q = nextqid;
	if (q > NQENT) {		/* Check for table overflow	*/
		return SYSERR;
	}

	nextqid += 2;			/* Increment index for next call*/

	/* Initialize head and tail nodes to form an empty queue */

	myqueuetab[queuehead(q)].qnext = queuetail(q);
	myqueuetab[queuehead(q)].qprev = EMPTY;
	myqueuetab[queuehead(q)].qkey  = MAXKEY;
	myqueuetab[queuetail(q)].qnext = EMPTY;
	myqueuetab[queuetail(q)].qprev = queuehead(q);
	myqueuetab[queuetail(q)].qkey  = MINKEY;
	return q;
}
