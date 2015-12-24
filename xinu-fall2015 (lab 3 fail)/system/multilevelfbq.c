#include <xinu.h>

struct mlqentry mlqtable[MLQENT];

pid32 mlqenqueue(pid32 pid, qid16 q) {
	//get pid prprio enqueue pid to that number's column
	kprintf("\n\nENQUEING===========\n\n");
	struct procent *proc;
	proc = &proctab[pid];
	int row = proc->prprio;
	int otherpid = enqueue(pid, mlqtable[row].queuetable);
	kprintf("PID ENQUEUED: %d      %d\n\n", pid, otherpid);
	return pid;
}

/*pid32 mlqdequeue(qid16 q) {

	kprintf("IN DEQUEUEADKFDJSLKAFJA ======\n\n");
	int count = MLQENT - 1;
	int pid;
	while (count >= 0) {
		kprintf("DEQUEUE: %d\n", count);
		pid = dequeue(mlqtable[count].queuetable);
		if (pid == -1) {
			count--;
			continue;
		} else {
			return pid;
		}
	}

}*/
pid32 mlqdequeue(qid16 q) {

	int count = MLQENT - 1;
	while (count >= 0) {

		if (getfirst(mlqtable[count].queuetable) != EMPTY) {
			return dequeue(mlqtable[count].queuetable);
		}
		count--;

	}

}
/*pid32	dequeue(
	  qid16		q		
	)
{
	pid32	pid;		

	if (isbadqid(q)) {
		return SYSERR;
	} else if (isempty(q)) {
		return EMPTY;
	}

	pid = getfirst(q);
	queuetab[pid].qprev = EMPTY;
	queuetab[pid].qnext = EMPTY;
	return pid;
}*/