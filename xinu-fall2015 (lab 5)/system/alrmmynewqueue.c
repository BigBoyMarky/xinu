/* newqueue.c - newqueue */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  newqueue  -  Allocate and initialize a queue in the global queue table
 *------------------------------------------------------------------------
 */
qid16	alrmmynewqueue(void)
{
	static qid16	nextqid=NPROC;	/* Next list in queuetab to use	*/
	qid16		q;		/* ID of allocated queue 	*/

	q = nextqid;
	if (q > alrmmyNQENT) {		/* Check for table overflow	*/
		return SYSERR;
	}

	nextqid += 2;			/* Increment index for next call*/

	/* Initialize head and tail nodes to form an empty queue */

	alrmmyqueuetab[alrmmyqueuehead(q)].qnext = alrmmyqueuetail(q);
	alrmmyqueuetab[alrmmyqueuehead(q)].qprev = EMPTY;
	alrmmyqueuetab[alrmmyqueuehead(q)].qkey  = MAXKEY;
	alrmmyqueuetab[alrmmyqueuetail(q)].qnext = EMPTY;
	alrmmyqueuetab[alrmmyqueuetail(q)].qprev = alrmmyqueuehead(q);
	alrmmyqueuetab[alrmmyqueuetail(q)].qkey  = MINKEY;
	return q;
}
