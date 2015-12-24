/* queue.h - firstid, firstkey, isempty, lastkey, nonempty		*/

/* Queue structure declarations, constants, and inline functions	*/

/* Default # of queue entries: 1 per process plus 2 for ready list plus	*/
/*			2 for sleep list plus 2 per semaphore		*/
#ifndef myNQENT
#define myNQENT	(3 * NPROC)
#endif

extern	struct qentry	myqueuetab[];

/* Inline queue manipulation functions */

#define	myqueuehead(q)	(q)
#define	myqueuetail(q)	((q) + 1)
#define	myfirstid(q)	(myqueuetab[myqueuehead(q)].qnext)
#define	mylastid(q)	(myqueuetab[myqueuetail(q)].qprev)
#define	myisempty(q)	(myfirstid(q) >= NPROC)
#define	mynonempty(q)	(myfirstid(q) <  NPROC)
#define	myfirstkey(q)	(myqueuetab[myfirstid(q)].qkey)
#define	mylastkey(q)	(myqueuetab[ mylastid(q)].qkey)

/* Inline to check queue id assumes interrupts are disabled */

#define	myisbadqid(x)	(((int32)(x) < 0) || (int32)(x) >= myNQENT-1)
