#include <xinu.h>

void mlfbqnewqueue(void)
{

	int count = 0;
	while (count < MLQENT) {

		mlqtable[count].queuetable = newqueue();
		kprintf("qid: %d\n", mlqtable[count].queuetable);
		count++;
	}

}
