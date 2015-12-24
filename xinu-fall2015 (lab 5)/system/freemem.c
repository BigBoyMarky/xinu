/* freemem.c - freemem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  freemem  -  Free a memory block, returning the block to the free list
 *------------------------------------------------------------------------
 */
syscall	freemem(
	  char		*blkaddr,	/* Pointer to memory block	*/
	  uint32	nbytes		/* Size of block in bytes	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	memblk	*next, *prev, *block;
	uint32	top;
	struct procent *prptr = &proctab[currpid];
	struct memblk *usedPrev;
	struct memblk *usedCurr;

	mask = disable();
	if ((nbytes == 0) || ((uint32) blkaddr < (uint32) minheap)
			  || ((uint32) blkaddr > (uint32) maxheap)) {
		restore(mask);
		return SYSERR;
	}

	uint32	gbheader = (uint32) roundmb(sizeof(struct memblk)); // header to point to the next used block for the process

	nbytes = (uint32) roundmb(nbytes) + gbheader;	/* Use memblk multiples	*/
	block = (struct memblk *) ((uint32)blkaddr - gbheader);

	prev = &memlist;			/* Walk along free list	*/
	next = memlist.mnext;
	while ((next != NULL) && (next < block)) {
		prev = next;
		next = next->mnext;
	}

	// when freeing the block of memory, also remove that block from the memoryBlocks list in the process
	usedPrev = &prptr->memoryBlocks;
	usedCurr = prptr->memoryBlocks.mnext;
	
	while (usedCurr != NULL) { // looking for the block of memory in the list that corresponds to the block passed into freemem
		//kprintf("FREEMEM block: %d   length: %d\n", usedPrev, usedCurr->mlength);
		if (usedCurr == (struct memblk *) block) {
			break;
		}
		usedPrev = usedCurr;
		usedCurr = usedCurr->mnext;
	}

	if (usedCurr != NULL) { // removing the block of memory from the used memoryBlocks list in the process
		usedPrev->mnext = usedCurr->mnext;
	}

	else { // that means that the block of memory being free'd is called from freestk
		block = (struct memblk *)blkaddr;
		nbytes = nbytes - gbheader;
	}


	if (prev == &memlist) {		/* Compute top of previous block*/
		top = (uint32) NULL;
	} else {
		top = (uint32) prev + prev->mlength;
	}

	/* Ensure new block does not overlap previous or next blocks	*/

	if (((prev != &memlist) && (uint32) block < top)
	    || ((next != NULL)	&& (uint32) block+nbytes>(uint32)next)) {
		restore(mask);
		return SYSERR;
	}

	memlist.mlength += nbytes;

	/* Either coalesce with previous block or add to free list */

	if (top == (uint32) block) { 	/* Coalesce with previous block	*/
		prev->mlength += nbytes;
		block = prev;
	} else {			/* Link into list as new node	*/
		block->mnext = next;
		block->mlength = nbytes;
		prev->mnext = block;
	}

	/* Coalesce with next block if adjacent */

	if (((uint32) block + block->mlength) == (uint32) next) {
		block->mlength += next->mlength;
		block->mnext = next->mnext;
	}
	restore(mask);
	return OK;
}
