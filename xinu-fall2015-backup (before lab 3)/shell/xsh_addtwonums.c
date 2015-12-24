#include <xinu.h>
#include <stdio.h>

/*----------------------------------------------------------------------------------------
 * xhs_addtwonums - a command that will add the two arguments together and display the sum
 * ---------------------------------------------------------------------------------------
 */
shellcmd xsh_addtwonums(int nargs, char *args[])
{

	int sum = atoi(args[1]) + atoi(args[2]);
	printf("The sum of the two numbers is: %d\n", sum);

	return 0;

}
