/* insertd.c - insertd */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  insertd  -  Insert a process in delta list using delay as the key
 *------------------------------------------------------------------------
 */
status	alrminsertd(			/* Assumes interrupts disabled	*/
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Delay from "now" (in ms.)	*/
	)
{
	int32	next;			/* Runs through the delta list	*/
	int32	prev;			/* Follows next through the list*/

	if (alrmmyisbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	prev = alrmmyqueuehead(q);
	next = alrmmyqueuetab[alrmmyqueuehead(q)].qnext;
	while ((next != alrmmyqueuetail(q)) && (alrmmyqueuetab[next].qkey <= key)) {
		key -= alrmmyqueuetab[next].qkey;
		prev = next;
		next = alrmmyqueuetab[next].qnext;
	}

	/* Insert new node between prev and next nodes */

	alrmmyqueuetab[pid].qnext = next;
	alrmmyqueuetab[pid].qprev = prev;
	alrmmyqueuetab[pid].qkey = key;
	alrmmyqueuetab[prev].qnext = pid;
	alrmmyqueuetab[next].qprev = pid;
	if (next != alrmmyqueuetail(q)) {
		alrmmyqueuetab[next].qkey -= key;
	}

	return OK;
}
