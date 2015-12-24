#include <xinu.h>

process lab0app2(void) {

	int x = 3782 * 751;
	kprintf("\n3782 times 751 = %d\n", x);
	kprintf("Lab0app2 has an id of: %d\n", getpid());
	kill(getpid());
}
