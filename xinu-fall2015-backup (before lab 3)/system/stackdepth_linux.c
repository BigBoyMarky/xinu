/*
 *
 * how to compile:
 * gcc -w -m32 -I ../include -o stackdepth_linux stackdepth_linux.c
 *
 * how to run:
 * ./stackdepth_linux
 *
 */

#include <xinu.h>

//static unsigned long *top_esp;
//static unsigned long *top_ebp;

int stackdepth_linux() {

	//struct procent *proc = &proctab[getpid()];

	unsigned long *top_esp;
	unsigned long *top_ebp;

	unsigned long *sp;
	unsigned long *fp;

	//asm("movl %esp, top_esp");
	//asm("movl %ebp, top_ebp");

	asm("movl %%esp, %0" : "=r" (top_esp));
	asm("movl %%ebp, %0" : "=r" (top_ebp));

	sp = top_esp;
	fp = top_ebp;

	int count = 0;

/*	while (fp <= (unsigned long *)proc->prstkbase) {

		kprintf("\nFP: %d\n", fp);
		fp++;
		count++;

	}
*/
//	kprintf("\nPROC->PRSTKBASE: %d\n", (unsigned long *)proc->prstkbase);
//	kprintf("HEXA: %x\n", (unsigned long *)proc->prstkbase);

	//while (sp < (unsigned long *)proc->prstkbase) {

	while (fp != NULL ) {
		/*if (sp == fp) {

			break;

		}*/
		printf("\nEBP: 0x%x ESP: 0x%x COUNT: %d", fp, sp, count);
		printf("\nStack frame size: %d", fp - sp);

		while (sp < fp) {

//			kprintf("\nFP: %d SP: %d hexFP: %x hexSP: %x", fp, sp, fp, sp);
//			kprintf("\nEBP: 0x%x ESP: 0x%x COUNT: %d", fp, sp, count);
//			kprintf("\nStack frame size: %d", fp - sp);
			sp++;

		}

//		fp++;
		fp = (unsigned long *) *(sp++);
//		fp = *++fp;
		count++;
//		kprintf("\nOUTERLOOP FP: %d SP: %d hexFP: %x hexSP: %x", fp, sp, fp, sp);
//		kprintf("\nEBP: 0x%x ESP: 0x%x",fp, sp);
//		kprintf("\nCOUNT: %d", count);
		sp++;

	}

	//printf("\nAddress at bottom: 0x%x\n", proc->prstkbase);

	return count;

}

/*main() {

	printf("\nStack depth in main: %d\n", stackdepth_linux());
	foo();
	doublefoo();
	//fooforever();

}*/

void foo() {

	printf("\nStack depth in foo: %d\n", stackdepth_linux());

}

void doublefoo() {

	printf("\nThis is in double foo:");
	foo();

}

void fooforever() {

	printf("\nThis is foo forever:");
	foo();
	fooforever();

}
