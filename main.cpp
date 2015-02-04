#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>


int main() 
{
	int nums[10] = {1,2,3,4,5,6,7,8,9,10};
	pid_t pid;
	
	int cpuToMem [2];
	int memTocpy [2];
	pipe(cpuToMem)
	pipe(memTocpy)
	pid = fork();
	if (pid < 0) //error checking fork
	{
		printf("Error Forking\n");
	}
	else if (pid == 0) //child process
	{
		printf("in Child Process\n");
	}
	else 
	{
		printf("Parent Process\n");
	}








	return 0;
}