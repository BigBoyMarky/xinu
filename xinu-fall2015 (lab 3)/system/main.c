/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{

	kprintf("MAIN\n\n\n\n\n\n\n");


	int cpuintensiveA = create(cpuintensive, 1024, 1, "cpuintensiveA", 0);
	int cpuintensiveB = create(cpuintensive, 1024, 1, "cpuintensiveB", 0);
	int cpuintensiveC = create(cpuintensive, 1024, 1, "cpuintensiveC", 0);
	int cpuintensiveD = create(cpuintensive, 1024, 1, "cpuintensiveD", 0);
	int cpuintensive1 = create(cpuintensive, 1024, 1, "cpuintensiveA", 0);
	int cpuintensive2 = create(cpuintensive, 1024, 1, "cpuintensiveB", 0);
	int cpuintensive3 = create(cpuintensive, 1024, 1, "cpuintensiveC", 0);
	int cpuintensive4 = create(cpuintensive, 1024, 1, "cpuintensiveD", 0);
	int cpuintensive5 = create(cpuintensive, 1024, 1, "cpuintensiveA", 0);
	int cpuintensive6 = create(cpuintensive, 1024, 1, "cpuintensiveB", 0);
	int cpuintensive7 = create(cpuintensive, 1024, 1, "cpuintensiveC", 0);
	int cpuintensive8 = create(cpuintensive, 1024, 1, "cpuintensiveD", 0);
	int cpuintensive9 = create(cpuintensive, 1024, 1, "cpuintensiveA", 0);
	int cpuintensive10 = create(cpuintensive, 1024, 1, "cpuintensiveB", 0);
	int cpuintensive11 = create(cpuintensive, 1024, 1, "cpuintensiveC", 0);
	int cpuintensive12 = create(cpuintensive, 1024, 1, "cpuintensiveD", 0);
	int cpuintensive13 = create(cpuintensive, 1024, 1, "cpuintensiveA", 0);
	int cpuintensive14 = create(cpuintensive, 1024, 1, "cpuintensiveB", 0);
	int cpuintensive15 = create(cpuintensive, 1024, 1, "cpuintensiveC", 0);
	int cpuintensive16 = create(cpuintensive, 1024, 1, "cpuintensiveD", 0);
	int cpuintensive17 = create(cpuintensive, 1024, 1, "cpuintensiveA", 0);
	int cpuintensive18 = create(cpuintensive, 1024, 1, "cpuintensiveB", 0);
	int cpuintensive19 = create(cpuintensive, 1024, 1, "cpuintensiveC", 0);
	int cpuintensive20 = create(cpuintensive, 1024, 1, "cpuintensiveD", 0);

	/*int iointensiveA = create(iointensive, 1024, 1, "iointensiveA", 0);
	int iointensiveB = create(iointensive, 1024, 1, "iointensiveB", 0);
	int iointensiveC = create(iointensive, 1024, 1, "iointensiveC", 0);
	int iointensiveD = create(iointensive, 1024, 1, "iointensiveD", 0);*/

	resume(cpuintensiveA);
	resume(cpuintensiveB);
	resume(cpuintensiveC);
	resume(cpuintensiveD);
	resume(cpuintensive1);
	resume(cpuintensive2);
	resume(cpuintensive3);
	resume(cpuintensive4);
	resume(cpuintensive5);
	resume(cpuintensive6);
	resume(cpuintensive7);
	resume(cpuintensive8);
	resume(cpuintensive9);
	resume(cpuintensive10);
	resume(cpuintensive11);
	resume(cpuintensive12);
	resume(cpuintensive13);
	resume(cpuintensive14);
	resume(cpuintensive15);
	resume(cpuintensive16);
	resume(cpuintensive17);
	resume(cpuintensive18);
	resume(cpuintensive19);
	resume(cpuintensive20);

    /*resume(iointensiveA);
	resume(iointensiveB);
	resume(iointensiveC);
	resume(iointensiveD);*/

	recvclr();


	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	//sleepms(5000);

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
