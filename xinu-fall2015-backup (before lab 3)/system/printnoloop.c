#include <xinu.h>

void printnoloop(char val) {

	kprintf("%c", val);
	kprintf("\nStack depth in printnoloop: %d\n", stackdepth());
	//stacktrace(currpid);
	sleepms(10000);

}
