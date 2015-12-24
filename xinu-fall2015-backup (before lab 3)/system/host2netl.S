.global host2netl

host2netl:
	
	pushl %ebp
	movl %esp, %ebp
	movl 8(%esp), %eax

	bswap %eax

	leave
	ret
