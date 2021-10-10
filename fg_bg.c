#include "headers.h"

extern struct Proc proc[100];


void FG(char *argumants[100], int no_of_arguments)
{
    if (no_of_arguments > 1)
    {
        printf("To many arguments\n");
        return;
    }

    int job_no = atoi(argumants[0]);
    int pid = proc[job_no].pid;
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, pid);

    signal(SIGINT, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    int err = kill(pid, SIGCONT);
    if(err < 0)
    {
        perror("fg");
        return;
    }
    proc[job_no].type = 0;
    int stat;
    waitpid(pid, &stat, WUNTRACED);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, getpid());
    signal(SIGTTOU, SIG_DFL);

    signal(SIGINT, SIG_IGN);

    UPDATE_JOBS();
    return;
}


void BG(char *argumants[100], int no_of_arguments)
{
    if (no_of_arguments > 1)
    {
        printf("To many arguments\n");
        return;
    }

    int job_no = atoi(argumants[0]);
    int pid = proc[job_no].pid;
    
    int err = kill(pid, SIGCONT);
    if(err < 0)
    {
        perror("bg");
        return;
    }
    proc[job_no].type = 1;
    UPDATE_JOBS();
    return;
}

