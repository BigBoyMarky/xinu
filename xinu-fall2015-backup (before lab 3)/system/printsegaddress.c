#include <xinu.h>

void printsegaddress() {

	kprintf("Start of text: 0x%08x\n", &text);
	kprintf("End of text: 0x%08x\n", &etext);
	kprintf("Start of data: 0x%08x\n", &data);
	kprintf("End of data: 0x%08x\n", &edata);
	kprintf("Start of bss: 0x%08x\n", &bss);
	kprintf("End of bss: 0x%08x\n", &ebss);

	kprintf("Length of text: %d\n", &etext - &text);
	kprintf("Length of data: %d\n", &edata - &data);
	kprintf("Length of bss: %d\n", &ebss - &bss);

//	kprintf("\nSTACK DEPTH IN PRINTSEGADDRESS: %d\n", stackdepth());

}
