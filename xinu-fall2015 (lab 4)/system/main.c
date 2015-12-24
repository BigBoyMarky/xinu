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


process	main(void)
{

	kprintf("MAIN\n\n\n\n\n\n\n");

/*	int test = create(testReceive, 1024, 2, "testReceive", 0);
	resume(test);

	resume(create(testSend, 1024, 1, "sendA", 2, test, 1));
	//sleepms(100);
	resume(create(testSend, 1024, 1, "sendB", 2, test, 2));
	//sleepms(100);
	resume(create(testSend, 1024, 1, "sendC", 2, test, 3));
	//sleepms(100);
	resume(create(testSend, 1024, 1, "sendD", 2, test, 4));*/


	/*int testAReceive = create(testAReceiver, 2014, 20, "testAsynchronousReceive", NULL);
	resume(testAReceive);
	*/
	if (registercb(&myrecvhandler) != OK) {
		kprintf("recv handler registration failed\n");
    	return 1;
	}

	int testAReceive = currpid;

	int testASend1 = create(testASender, 2048, 20, "testAsynchronousSend", 2, testAReceive, 1);
	int testASend2 = create(testASender, 2048, 20, "testAsynchronousSend", 2, testAReceive, 2);
	int testASend3 = create(testASender, 2048, 20, "testAsynchronousSend", 2, testAReceive, 3);
	int testASend4 = create(testASender, 2048, 20, "testAsynchronousSend", 2, testAReceive, 4);
	resume(testASend1);
	resume(testASend2);
	resume(testASend3);
	resume(testASend4);

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