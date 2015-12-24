/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	clktimefine++;

	struct procent *prptr = &proctab[currpid];

	// here I would decrement the counter until it reaches 0.  once it reaches 0, I know that cpu time is up and need to call the cpu callback function
	if (prptr->xcpuPointer != NULL) {
		prptr->xcpuTime--;
		if (prptr->xcpuTime == 0) {
			// generate xcpu callback function;
			void (*xcpuFunc) () = prptr->xcpuPointer;
			prptr->xcpuPointer = NULL;
			xcpuFunc();
		}
	}

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	// similar to how wakeup works but I check for a nonempty alrmqueue
	if (alrmmynonempty(alrmqueue)) {
		if((--alrmmyqueuetab[alrmmyfirstid(alrmqueue)].qkey) <= 0) { // decrement the alrmqueue delta list's first item's key
			alrmmywakeup(); // once 0 is hit, call alrmmywakeup
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
}
