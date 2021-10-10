#include "headers.h"
extern struct Proc proc[100];
extern int no_of_jobs;

void child_died(int signal)
{

    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG | WUNTRACED);

    if (pid > 0)
    {
        for (int i = 0; i < no_of_jobs; i++)
        {
            if (WIFEXITED(status) && pid == proc[i].pid)
            {
                fprintf(stderr, "\n%s with pid: %d exited normally, status = %d\n", proc[i].name, pid, WEXITSTATUS(status));
                UPDATE_JOBS();
            }

            fflush(stdout);
        }
    }
}

void ctrl_Z()
{

    for (int i = 0; i < no_of_jobs; i++)
    {
        // char* argumants[100];
        // sprintf(argumants[0], "%d", i);
        // // kill(proc[i].pid, SIGTTIN);
        // kill(proc[i].pid, SIGTSTP);
        // BG(argumants, 1);
        
        kill(proc[i].pid, SIGTSTP);

        tcsetpgrp(STDIN_FILENO, getpid());
        signal(SIGTTOU, SIG_DFL);

        signal(SIGINT, SIG_IGN);

        UPDATE_JOBS();
    }
    UPDATE_JOBS();
    return;
}
