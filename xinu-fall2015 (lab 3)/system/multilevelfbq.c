#include <xinu.h>

struct mlqentry mlqtable[60][NPROC];

void mlqenqueue(pid32 pid) {
	//kprintf("ENQUEUE %d\n", pid);
	struct procent *proc = &proctab[pid];

//	if (proc->prstate == PR_READY) {

	int priority = proc->prprio;

	mlqtable[priority][mlqstartendtable[priority].end%NPROC].processID = pid;
	mlqstartendtable[priority].end++;

	//kprintf("ENEQUEUED: %d\n",pid);
	//kprintf("MLQENQUEUE %d   %d\n", pid, priority);
	//int i = 0;
	///int existing = 0;
	//while (mlqtable[priority][i].processID != -1) {
		/*if (mlqtable[priority][i].processID == pid) {
			existing = 1;
		}*/
	//	i++;
	//}
	//if (existing == 0)
		//mlqtable[priority][i].processID = pid;

	/*pid32 test = mlqdequeue();
	kprintf("ENQUING DEQUEED: %d\n", test);
	mlqenqueue(test);*/
	/*int k = 0;
	while (k < NPROC) {
		kprintf("%d ", mlqtable[priority][k].processID);
		k++;
	}
	kprintf("\n");*/
//	}

}

pid32 mlqdequeue() {
	int i = 59;
	while (mlqtable[i][mlqstartendtable[i].start%NPROC].processID == EMPTY) {
		i--;
		if (i == -1)
			return 0;
	}

	pid32 ret = mlqtable[i][mlqstartendtable[i].start%NPROC].processID;
	mlqtable[i][mlqstartendtable[i].start%NPROC].processID = EMPTY;
	mlqstartendtable[i].start++;

	if (ret == -1)
		return 0;

	//kprintf("DEQUEUE %d %d\n", EMPTY, ret);
	return ret;
	/*pid32 ret = -1;
	int i = 59;
	while (mlqtable[i][0].processID == -1){
	//	kprintf("i: %d\n", i);
		i--;
	}
	if (i == -1)
		return 0;
	ret = mlqtable[i][0].processID;*/
	//kprintf("DEQUEUED: %d\n",ret);

	/*if (ret == 26) {
		int a;
		int b;
		for (a = 0; a < ROWS; a++) {
			for (b = 0; b < NPROC; b++) {
				kprintf("%d ", mlqtable[a][b].processID);
			}
			kprintf("\n");
		}
	}*/
	/*mlqtable[i][0].processID = -1;
	int j = 1;
	while (mlqtable[i][j].processID != -1){
		//kprintf("j: %d      %d       %d\n", j, mlqtable[i][j].processID, EMPTY);
		mlqtable[i][j - 1] = mlqtable[i][j];
		mlqtable[i][j].processID = -1;
		j++;
	}*/
	/*if(ret == EMPTY)
		kprintf("We're returning EMPTY\n\n");*/
	//kprintf("MLQDEQUEUE %d\n", ret);
	/*int k = 0;
	while (k < NPROC) {
		kprintf("%d ", mlqtable[i][k].processID);
		k++;
	}
	kprintf("\n");*/

//	return ret;

}

pid32 mlqprioritypeek() {

	//kprintf("MLQPEEK\n");
	int i = 59;
	while (mlqtable[i][0].processID == -1){
		i--;
	}
	return i;

}
