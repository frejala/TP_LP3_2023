#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

sig_atomic_t child_exit_status;

void clean_up_child_process(int signal_number)
{
    /* Clean up the child process. */
    int status;
    wait(&status);
    /* Store its exit status in a global variable. */
    child_exit_status = status;
}

int main()
{
    /* Handle SIGCHLD by calling clean_up_child_process. */
    struct sigaction sigchld_action;
    memset(&sigchld_action, 0, sizeof(sigchld_action));
    sigchld_action.sa_handler = &clean_up_child_process;
    sigaction(SIGCHLD, &sigchld_action, NULL);

    /* Do some lengthy stuff here. */
    /* ... */
    pid_t child_pid = fork();

    if (child_pid == 0)
    {
        for (size_t i = 0; i < 100000; i++)
        {
            if (i % 20000 == 0)
            {
                printf("Child running...\n");
                sleep(1);
            }
        }
        exit(0);
    }
    else
    {
        printf("Parent process, waiting for child to finish\n");
        wait(&child_exit_status);

        for (size_t i = 0; i < 1000; i++)
        {
            if (i % 200 == 0)
            {
                printf("Parent running...\n");
                sleep(1);
            }
        }

        return 0;
    }
}
