#include <xinu.h>

//syscall registercb(int (*myrecvhandler)(void)) {
syscall registercbsig( uint16 asig, int(* func)(void), uint32 optarg) {

	intmask mask;
	mask = disable();

	//if (myrecvhandler == NULL) {
	if (func == NULL) {
		restore(mask);
		return SYSERR;
	}

	if (asig == MYSIGRECV) {
		struct procent	*prptr = &proctab[currpid];
		prptr->hasCBFunction = TRUE; // that means that receive has a callback function
		//prptr->cbPointer = myrecvhandler; // store the pointer of myrecvhandler function to cbPointer
		prptr->cbPointer = func;
		restore(mask);
		return OK;
	} else if (asig == MYSIGALRM) { // check for MYSIGALRM
		//user callback function is invoked when a timer expires (timer time = optarg)
		//sleepms(optarg);
		struct procent *prptr = &proctab[currpid];

		if(prptr->alrmPointer != NULL) { // if there is an existing alrm, overwrite it
			prptr->alrmPointer = func;
			prptr->alrmTime = optarg;
			alrminsertd(alrmmygetitem(currpid), alrmqueue, optarg);
		} else {
			//prptr->hasCBFunction = TRUE;
			prptr->alrmPointer = func;
			prptr->alrmTime = optarg;
			//kprintf("time prior to alrm: %d\n", clktimefine);
			alrminsertd(currpid, alrmqueue, optarg); // inserted the process into the delta list that stores all the alarms	
		}
		restore(mask);
		return OK;
	} else { //check when asig == MYSIGXCPU
		//kprintf("time prior to xcpu: %d\n", clktimefine);
		struct procent *prptr = &proctab[currpid];
		//prptr->hasCBFunction = TRUE;
		prptr->xcpuPointer = func;
		prptr->xcpuTime = optarg;
		restore(mask);
		return OK;
	}
	//restore(mask);
	//return OK;
}
