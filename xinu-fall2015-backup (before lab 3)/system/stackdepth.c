#include <xinu.h>

//static unsigned long *top_esp;
//static unsigned long *top_ebp;

int stackdepth() {

	struct procent *proc = &proctab[currpid];

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

	while (sp < (unsigned long *)proc->prstkbase) {

		/*if (sp == fp) {

			break;

		}*/
		kprintf("\nEBP: 0x%x ESP: 0x%x COUNT: %d", fp, sp, count);
		kprintf("\nStack frame size: %d", fp - sp);

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

	kprintf("\nAddress at bottom: 0x%x\n", proc->prstkbase);

	return count;

}
