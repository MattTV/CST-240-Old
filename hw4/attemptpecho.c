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
    pid_t rproc = fork();

    if (wproc == -1 || rproc == -1)
        fatal_error("Unable to fork.");

    else if (!wproc && !rproc)
    {
        if (close(pipefd[0]) || close(pipefd[1]))
            fatal_error("Failed to close.");
        printf("Sup tard");
    }

    else if (wproc)
    {
        if (close(pipefd[0]))
            fatal_error("Failed to close.");
        printf("Sup, dingus?");
    }


    else if (rproc)
    {
        if (close(pipefd[1]))
            fatal_error("Failed to close.");
        printf("Hah, look at that retard");
    }

    if (getpid() == wproc)
    {
        char command[] = "./wchild";
        free(argv[0]);
        argv[0] = command;

        dup2(pipefd[1],1);

        if (execvp(argv[0], argv))
            fatal_error("Unable to execute wchild.");

        if (close(pipefd[0]))
            fatal_error("Failed to close.");

        exit(0);
    }

    else if (getpid() == rproc)
    {
        dup2(pipefd[0],0);
        
        if(execvp("./rchild", NULL))
            fatal_error("Unable to execute rchild.");

        if (close(pipefd[1]))
            fatal_error("Failed to close."); 

        exit(0);
    }

    else
    {
        wait(NULL);
        wait(NULL);
    }

    //if (pclose(pipefd) == -1) 
    //    fatal_error("Failed to close whole pipe.");
    
    return 0;
}
