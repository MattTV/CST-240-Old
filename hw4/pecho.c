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

    // Open the pipe.
    if (pipe(pipefd) == -1)
        fatal_error("Unable to open pipe.");

    // Create the fork for the wchild process.
    pid_t wproc = fork();

    if (wproc == -1)
        fatal_error("Unable to fork wproc.");

    // wproc process
    else if (wproc == 0)
    {
        // Close the input pipe.
        if (close(pipefd[0]))
            fatal_error("Failed to close pipefd[0] in wproc.");

        // Change argv to be used to run wchild instead.
        char command[] = "./wchild";
        argv[0] = command;

        // Call wchild.
        if (execvp(argv[0], argv))
            fatal_error("Unable to execute wchild.");

        // Close the pipe.
        if (close(pipefd[1]))
            fatal_error("Failed to close pipefd[1] in wproc.");

        // Close the process.
        exit(0);
    }

    // Parent process
    else
    {
        // Wait for wchild to finish.
        wait(NULL);

        // Create the rchild process.
        pid_t rproc = fork();
        if (rproc == -1)
            fatal_error("Unable to fork rproc.");

        // rproc process
        if (rproc == 0)
        {
            // Close the output pipe.
            if (close(pipefd[1]))
                fatal_error("Failed to close pipefd[1] in rproc.");

            // Prep to use execvp for rchild with no arguments, and use it.
            char * args[] = {"./rchild",NULL};
            if (execvp(args[0], args))
                fatal_error("Unable to execute rchild.");

            // Close the pipe.
            if (close(pipefd[0]))
                fatal_error("Unable to close input pipefd[0] in rproc.");

            // Close the process.
            exit(0);
        }
    }

    // I thought I shoudl do pclose here, but it gives a segmentation fault, which I'm guessing is because I close the pipe on both sides in other places?

    return 0;
}
