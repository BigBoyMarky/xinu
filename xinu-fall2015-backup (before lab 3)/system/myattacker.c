#include <xinu.h>

void myattacker(void) {

	struct procent *proc = &proctab[currpid - 1];
//	unsigned long *fp = proc->prstkbase;

/*	struct procent *prevproc = &proctab[currpid];
	unsigned long *prevfp = prevproc->prstkbase;*/

	//fp =- 9;

	//struct procent *proc2 = &proctab[currpid - 2];
	//unsigned long *sp = (unsigned long *)proc2->prstkbase;
	unsigned long *fp = (unsigned long *)proc->prstkbase;

//	struct procent *proc2 = &proctab[currpid];
//	unsigned long *fp2 = (unsigned long *)proc->prstkbase;

//	while ) {
//		kprintf("fp: %d\n", fp);
//		fp--;

//	}
//	while (fp > fp2)
//		fp--;
	fp-= 2;
	*fp = &myattackermalware;

}
