#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void fatal_error(const char *msg)
{
    perror(msg);
        exit(1);
}

int main(int argc, char * argv[])
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
        fatal_error("Unable to open pipe.");

    pid_t wproc = fork();

    if (wproc == -1)
        fatal_error("Unable to fork wproc.");

    // wproc process
    else if (wproc == 0)
    {
        if (close(pipefd[0]))
            fatal_error("Failed to close pipefd[0] in wproc.");

        char command[] = "./wchild";
        argv[0] = command;

        if (execvp(argv[0], argv))
            fatal_error("Unable to execute wchild.");

        if (close(pipefd[1]))
            fatal_error("Failed to close pipefd[1] in wproc.");

        exit(0);
    }

    // Parent process
    else
    {
        wait(NULL);

        pid_t rproc = fork();
        if (rproc == -1)
            fatal_error("Unable to fork rproc.");

        // rproc process
        if (rproc == 0)
        {
            wait(NULL);

            if (close(pipefd[1]))
                fatal_error("Failed to close pipefd[1] in rproc.");

            char * args[] = {"./rchild",NULL};
            if (execvp(args[0], args))
                fatal_error("Unable to execute rchild.");

            if (close(pipefd[0]))
                fatal_error("Unable to close input pipefd[0] in rproc.");

            exit(0);
        }
    }

    return 0;
}
