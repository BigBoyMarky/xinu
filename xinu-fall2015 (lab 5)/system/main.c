/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>


process testReceive(void) {
	while(TRUE) {
		//kprintf("before receive call\n");
		umsg32 testreceive = receive();
		//kprintf("after receive call\n");
		kprintf("\nRECEIVED: %d    %d\n", testreceive, clktimefine);
		sleepms(200);
	}
	//kprintf("exited while loop for some reason\n");
	return OK;
}

process testSend(pid32 pid, umsg32 msg) {
	//kprintf("before sendbt %d\n", msg);
	//kprintf("testsend: %d\n", msg);
	//if (sendbt(pid, msg, 1000) == OK) {
		//kprintf("OKAY  %d      %d\n", msg, clktimefine);
	//} else {
		//kprintf("TIMEOUT  %d     %d\n", msg, clktimefine);
	//}
	//kprintf("after sendbt %d\n", msg);
	kprintf("BEFORE PID: %d  TIME: %d\n", currpid, clktimefine);
	//sendbt(pid, msg, 0);
	sendbt(pid, msg, 100);
	kprintf("AFTER  PID: %d  TIME: %d\n", currpid, clktimefine);
	return OK;
}

int myrecvhandler(void) {

	extern umsg32 msgglob;
	msgglob = receive();
	kprintf("callback function pid: %d time: %d msg: %d\n", currpid, clktimefine, msgglob);
	return OK;

}

int myalrmhandler(void) {

	//extern umsg32 msgglob;
	//msgglob = receive();
	kprintf("alrm %d called at: %d\n", currpid, clktimefine);
	return OK;

}

int myxcpuhandler(void) {
	kprintf("xcpu %d called at: %d\n", currpid, clktimefine);
	return OK;
}

process testAsynchronousReceive(void) {

	if (registercb(&myrecvhandler) != OK) {
		kprintf("recv handler registration failed\n");
    	return 1;
	}

	while(TRUE) {
		sleepms(10);
	}

	return 0;
		//syscall registercb(int(*myrecvhandler)(void));

	// store the address of the callback function in it's process table entry
}

void testAReceiver() {

	if (registercb(&myrecvhandler) != OK) {
		kprintf("recv handler registration failed\n");
    	return;
	}

	while(TRUE) {
		sleepms(10);
	}

	return;
}

void testASender(pid32 receiver, umsg32 msg) {

	if( send(receiver, msg) == SYSERR ) {
		kprintf("Message failed %d\r\n", msg);
	} else {
		kprintf("Send succeeded %d\r\n", msg);
	}
	return;
}

void testSIGSender(pid32 receiver, umsg32 msg) {
	/*if (registercbsig(MYSIGRECV, &myrecvhandler, 500) != OK) {
		kprintf("recv handler registration failed\n");
    	return 1;
	}*/
	/*if (registercbsig(MYSIGALRM, &myalrmhandler, 500) != OK) {
		kprintf("alarm handler registration failed\n");
    	return 1;
	}*/
	if (registercbsig(MYSIGXCPU, &myxcpuhandler, 300) != OK) {
		kprintf("xcpu handler registration failed\n");
    	return 1;
	} else {
		kprintf("Send succeeded %d\r\n", msg);
	}

	while(TRUE) {
		sleepms(10);
	}

	return;
}

process testALRM(int16 t) {

	kprintf("before alrm %d called at: %d\n", currpid, clktimefine);
	if (registercbsig(MYSIGALRM, &myalrmhandler, t) != OK) {
		kprintf("myalrmhandler registration failed\n");
	}
	while (TRUE) {
		sleepms(10);
	}

}

process testXCPU(int16 t) {

	if (registercbsig(MYSIGXCPU, &myxcpuhandler, t) != OK) {
		kprintf("myxcpuhandler registration failed\n");
	}
	while (TRUE) {
		sleepms(10);
	}

}

void testgbgetmem() {

	kprintf("testgbgetmem\n");
	void *test1 = getmem(512);
	void *test2 = getmem(100);
	void *test3 = getmem(100);
	void *test4 = getmem(100);
	void *test5 = getmem(100);
	void *test6 = getmem(100);
	void *test7 = getmem(100);
	void *test8 = getmem(100);
	void *test9 = getmem(100);
	void *test10 = getmem(100);
	//void *test3 = gbgetmem(100);
	//void *test4 = gbgetmem(100);
	//void *test5 = gbgetmem(100);
	//void *test6 = gbgetmem(100);
	//void *test7 = gbgetmem(100);

	if (freemem(test1, 512) == SYSERR) {
		kprintf("freemem failed\n");
	}

	struct procent *prptr = &proctab[currpid];
	struct memblk *tcurr, *tprev;
	tprev = &prptr->memoryBlocks;
	tcurr = prptr->memoryBlocks.mnext;
	//kprintf("traverse %d\n", tcurr);
	/*	//tprev->mnext = tcurr->mnext;
		tprev = tcurr;
		tcurr = tcurr->mnext;
		kprintf("block: %d\n", tprev);
		//tprev->mnext = tcurr->mnext;
		tprev = tcurr;
		tcurr = tcurr->mnext;
		kprintf("block: %d\n", tprev);
		//tprev->mnext = tcurr->mnext;
		tprev = tcurr;
		tcurr = tcurr->mnext;
		kprintf("block: %d\n", tprev);*/
	/*while (tcurr != NULL) {
	//	tprev->mnext = tcurr->mnext;
		tprev = tcurr;
		tcurr = tcurr->mnext;
		kprintf("block: %d\n", tprev);
	}*/
}

process	main(void)
{

	kprintf("MAIN\n\n\n\n\n\n\n");

/*	if (registercbsig(MYSIGALRM, &myalrmhandler, 500) != OK) {
		kprintf("myalrmhandler registration failed\n");
	}*/
	/*if (registercbsig(MYSIGALRM, &myalrmhandler, 501) != OK) {
		kprintf("myalrmhandler registration failed\n");
	}*/

	/*resume( create(testALRM, 1024, 20, "ALARMTESTCASE",1, 500) );
	resume( create(testALRM, 1024, 20, "ALARMTESTCASE",1, 600) );
	resume( create(testALRM, 1024, 20, "ALARMTESTCASE",1, 700) );
	resume( create(testALRM, 1024, 20, "ALARMTESTCASE",1, 1000) );*/
	kprintf("MEMLIST: %d\n", memlist.mlength);
	resume( create(testgbgetmem, 1024, 20, "test gb", 0) );
	kprintf("MEMLIST: %d\n", memlist.mlength);
	sleepms(1000);
	kprintf("MEMLIST: %d\n", memlist.mlength);
	int testAReceive = currpid;

	while (TRUE) {

	}

	/*sleepms(5000);

	recvclr();


	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));*/



	/* Wait for shell to exit and recreate it */

	/*while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}*/

	return OK;

}


/*
#include <xinu.h>
#include <stdio.h>

void cb(){
  kprintf("pid %d alarmed at time %d\n", currpid, clktimefine);
}

process alarm_process(){
  registercbsig(MYSIGALRM, &cb, 50);
  registercbsig(MYSIGALRM, &cb, 20);
  kprintf("pid %d is going to sleep at time %d\n",currpid, clktimefine);
  sleep(10000);
  while(1);
}

process main(void){
  resume( create(alarm_process, 1024, 20, "ALARMTESTCASE",0) );
  while(1){
    sleepms(10);
  }
}
*/
