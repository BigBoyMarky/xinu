/* queue.h - firstid, firstkey, isempty, lastkey, nonempty		*/

/* Queue structure declarations, constants, and inline functions	*/

/* Default # of queue entries: 1 per process plus 2 for ready list plus	*/
/*			2 for sleep list plus 2 per semaphore		*/
#ifndef alrmmyNQENT
#define alrmmyNQENT	(3 * NPROC)
#endif

extern	struct qentry	alrmmyqueuetab[];

/* Inline queue manipulation functions */

#define	alrmmyqueuehead(q)	(q)
#define	alrmmyqueuetail(q)	((q) + 1)
#define	alrmmyfirstid(q)	(alrmmyqueuetab[alrmmyqueuehead(q)].qnext)
#define	alrmmylastid(q)	(alrmmyqueuetab[alrmmyqueuetail(q)].qprev)
#define	alrmmyisempty(q)	(alrmmyfirstid(q) >= NPROC)
#define	alrmmynonempty(q)	(alrmmyfirstid(q) <  NPROC)
#define	alrmmyfirstkey(q)	(alrmmyqueuetab[alrmmyfirstid(q)].qkey)
#define	alrmmylastkey(q)	(alrmmyqueuetab[ alrmmylastid(q)].qkey)

/* Inline to check queue id assumes interrupts are disabled */

#define	alrmmyisbadqid(x)	(((int32)(x) < 0) || (int32)(x) >= alrmmyNQENT-1)
