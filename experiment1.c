#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *arg[])
{
	int pid; pid = fork();
		if (pid < 0)
			{
				printf("fork failed");
				exit (1);
			}
		else if (pid == 0)
			{
				execlp("whoami", "is", NULL);
				exit (0);
			}
		else
			{
				printf("\nProcess ID is: %d\n", getpid());
				wait(NULL);
				exit (0);
			}
}