#include <xinu.h>

process lab0app1(void) {
	kprintf("\nHi this is lab0app1\n");
	kprintf("The process id is: %d\n", getpid());
//	kprintf("\nSTACK DEPTH IN LAB0APP1: %d\n", stackdepth());
	kill(getpid());
}
