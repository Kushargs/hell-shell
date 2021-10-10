#include "headers.h"
extern int no_of_jobs;
extern struct Proc proc[100];

void SIG(char *argumants[100], int no_of_arguments)
{
    if (no_of_arguments > 2)
    {
        printf("To many arguments\n");
        return;
    }
    int job_no = atoi(argumants[0]);
    int signum = atoi(argumants[1]);
    int err = kill(proc[job_no].pid, signum);
    if(err < 0)
    {
        perror("sig");
    }
}