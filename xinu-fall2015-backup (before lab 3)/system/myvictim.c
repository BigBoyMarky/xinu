#include <xinu.h>

void myvictim(void) {

	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	a = 100 * 2;
	b = 100 / 2;
	c = 100 - 2;
	d = 100 + 2;

	int sum = a + b + c + d;

	victimSleeper();

	kprintf("\nProcess ID of myvictim: %d\nmyvictimglobal: %d\n\n", currpid, myvictimglobal);

}

void victimSleeper() {

	int a = 0;
	int b = 0;

	a = a + 1000;
	b = b + 1000;

	int sum = a + b;

	sleepms(sum);

}
