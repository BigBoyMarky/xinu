#include <xinu.h>

syscall registercb(int (*myrecvhandler)(void)) {

	intmask mask;
	mask = disable();

	if (myrecvhandler == NULL) {
		restore(mask);
		return SYSERR;
	}

	struct procent	*prptr = &proctab[currpid];
	prptr->hasCBFunction = TRUE; // that means that receive has a callback function
	prptr->cbPointer = myrecvhandler; // store the pointer of myrecvhandler function to cbPointer

	restore(mask);
	return OK;
}