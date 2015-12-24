/* yield.c - yield */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  yield  -  Voluntarily relinquish the CPU (end a timeslice)
 *------------------------------------------------------------------------
 */
syscall	yield(void)
{
	intmask	mask;			/* Saved interrupt mask		*/

	mask = disable();

	struct procent *proc = &proctab[currpid];
	proc->prclassify = 0;
	cpuio();
	resched();
	restore(mask);
	return OK;
}
