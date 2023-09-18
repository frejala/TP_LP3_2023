#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
    pid_t child_pid;
    /* Create a child process. */
    child_pid = fork();
    if (child_pid > 0)
    {
        /* This is the parent process. Sleep for a minute. */
        sleep(60);
        printf("Parent process Done\n");
    }
    else
    {
        /* This is the child process. Exit immediately. */
        printf("Exiting child process\n");
        exit(0);
    }
    return 0;
}