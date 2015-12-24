#include <xinu.h>

struct mlqentry mlqtable[ROWS][NPROC];
struct mlqstartend mlqstartendtable[ROWS];

void	newmlqueue(void)
{
	int i = 0;
	int j;
	//kprintf("ROWS: %d\n", ROWS);
	for (;i < ROWS; i++) {
	//while(i < ROWS) {
		for (j = 0; j < NPROC; j++) {
		//while (j < NPROC) {
			mlqtable[i][j].processID = EMPTY;
			//kprintf("%d %d %d\n", i, j, mlqtable[i][j].processID);
			//j++;
		}
	/*	j = 0;
		i++;*/
	}
}
