#include <xinu.h>

void alrmmywakeup(void) {

	resched_cntl(DEFER_START);
	while (alrmmynonempty(alrmqueue) && (alrmmyfirstkey(alrmqueue) <= 0)) {
//		alrmmyready(alrmmydequeue(alrmqueue));
		pid32 pid = alrmmydequeue(alrmqueue);
		if (pid == currpid) { // if the pid of the alrm that needs to be woken up is equal to the currpid, then I can just run the callback function
			//pid32 pid = currpid;
			struct procent *prptr = &proctab[pid];
			void (*alrmFunc) () = prptr->alrmPointer;
			prptr->alrmPointer = NULL;
			alrmFunc();
/*			while (true) {
				if
			}*/
		} else {// if the pid of the alrm that needs to be woken up is not the currpid, then I need to set a flag unsleep and ready the 
			    //process so that when the process rescheds in, then the alarm callback function can be called
			//ready(alrmmygetitem(alrmqueue));
			//ready(dequeue(sleepq));
			struct procent *prptr = &proctab[pid];
			prptr->isALRMReady = TRUE;
			if (prptr->prstate == PR_SLEEP) { // i unsleep and ready the process
				unsleep(pid);
				ready(pid);
			}
			/*struct procent *ptcur = &proctab[currpid];
			prptr->prstate = PR_CURR;
			preempt = QUANTUM;
			ctxsw(&ptcur->prstkptr, &prptr->prstkptr);

			void (*alrmFunc) () = prptr->alrmPointer;
			prptr->alrmPointer = NULL;
			alrmFunc();

			ctxsw(&prptr->prstkptr, &ptcur->prstkptr);
			prptr->prstate = PR_READY;*/
		}
		/*else {
			pid32 alrmpid = alrmmydequeue(alrmqueue);
			struct procent *ptold;
			struct procent *ptnew;
			ptold = &proctab[currpid];
			ptnew = &proctab[alrmpid];
			ctxsw(&ptold->prstkptr, &ptnew->prstkptr);
			void (*alrmFunc) () = ptnew->alrmPointer;
			ptnew->alrmPointer = NULL;
			alrmFunc();
			ctxsw(&ptnew->prstkptr, &ptold->prstkptr);
		//	ctxsw(&ptold->prstkptr, &ptnew->pstkptr);
		}*/
	}

	resched_cntl(DEFER_STOP);

	return;

}
