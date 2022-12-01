#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main()
{
	int cpu_num = syscall(451);
	printf("cpu num = %d\n", cpu_num);

	return 0;
}
