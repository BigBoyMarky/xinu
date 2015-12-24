/* getmem.c - getmem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getmem  -  Allocate heap storage, returning lowest word address
 *------------------------------------------------------------------------
 */
char  	*getmem(
	  uint32	nbytes		/* Size of memory requested	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	memblk	*prev, *curr, *leftover;
	struct procent *prptr = &proctab[currpid];
	struct memblk *usedBlock;

	mask = disable();
	if (nbytes == 0) {
		restore(mask);
		return (char *)SYSERR;
	}

	uint32	gbheader = (uint32) roundmb(sizeof(struct memblk)); // header to point to the next used block for the process

	nbytes = (uint32) roundmb(nbytes) + gbheader;	/* Use memblk multiples	*/

	prev = &memlist;
	curr = memlist.mnext;
/*	if (prev == NULL) { // first time allocating heap memory
		prptr->memoryBlocks->mlength = nbytes;
		prptr->memoryBlocks->mnext = curr;
		restore(mask);
		return (char *) prev;
	}*/


	while (curr != NULL) {			/* Search free list	*/

		/*
		struct	memblk	{
			struct	memblk	*mnext;
			uint32	mlength;
		};*/


		if (curr->mlength == nbytes) {	/* Block is exact match	*/
			prev->mnext = curr->mnext;
			memlist.mlength -= nbytes;

			//usedBlock = (struct memblk *)curr;
			//usedBlock = curr;

			// I added the block of memory also into the memoryBlocks list to keep track of the used blocks of the process
			usedBlock = (struct memblk *) curr;
			usedBlock->mnext = prptr->memoryBlocks.mnext;
			usedBlock->mlength = nbytes;
			prptr->memoryBlocks.mnext = usedBlock;
			prptr->memoryBlocks.mlength = nbytes;
			//kprintf("added exact\n");
			//prptr->memoryBlocks->mnext = (struct memblk *)curr;
			//prptr->memoryBlocks->mnext = curr->mnext;
			//prptr->memoryBlocks->mlength = nbytes;
			/*
			struct memblk tempmemblk;
			memblk->mlength = nbytes;
			memblk->mnext = mnext;

			prptr->memoryBlocks->mlength = nbytes;*/

			//kprintf("allocated: %d\n", nbytes);
			restore(mask);
			return (char *)((uint32)curr + gbheader);

		} else if (curr->mlength > nbytes) { /* Split big block	*/
			leftover = (struct memblk *)((uint32) curr +
					nbytes);
			prev->mnext = leftover;
			leftover->mnext = curr->mnext;
			leftover->mlength = curr->mlength - nbytes;
			memlist.mlength -= nbytes;

			//usedBlock = (struct memblk *)curr;
			//usedBlock = curr;

			// I added the block of memory also into the memoryBlocks list to keep track of the used blocks of the process
			usedBlock = (struct memblk *) curr;
			usedBlock->mnext = prptr->memoryBlocks.mnext;
			usedBlock->mlength = nbytes;
			prptr->memoryBlocks.mnext = usedBlock;
			prptr->memoryBlocks.mlength = nbytes;
			//prptr->memoryBlocks->mlength = prptr->memoryBlocks->mlength + nbytes;
			//kprintf("added split %d\n",prptr->memoryBlocks.mnext);
			//prptr->memoryBlocks->mnext = (struct memblk *)curr;
			//prptr->memoryBlocks->mlength = nbytes;
			//kprintf("allocated: %d\n", nbytes);
			restore(mask);
			return (char *)((uint32)curr + gbheader);
		} else {			/* Move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}
	restore(mask);
	return (char *)SYSERR;
}
