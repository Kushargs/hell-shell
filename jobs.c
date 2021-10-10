#include "headers.h"
extern int no_of_jobs;
extern struct Proc proc[100];

void getstatus(int i)
{
    // printf("getting status\n");

    char status_file[buff_sz];
    char state;
    char status_R[100] = "Running";
    char status_S[100] = "Stopped";

    sprintf(status_file, "/proc/%d/stat", proc[i].pid);

    FILE *fd = fopen(status_file, "r");
    if (fd != NULL)
    {
        fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &state);
        fclose(fd);
        // printf("status: %c\n", state);
        if (state == 'T')
        {
            proc[i].stat = status_S;
        }
        else
        {
            proc[i].stat = status_R;
        }
    }
    else
    {
        proc[i].stat = status_S;
    }
}

void JOBS(char *arguments[100], int no_of_arguments)
{
    UPDATE_JOBS();
    int flg_r = 0;
    int flg_s = 0;

    for (int i = 0; i < no_of_arguments; i++)
    {
        if (strcmp(arguments[i], "-r") == 0)
            flg_r = 1;
        else if (strcmp(arguments[i], "-s") == 0)
            flg_s = 1;
    }

    // printf("flg_r: %d, flg_r:%d\n", flg_r, flg_s);

    for (int i = 0; i < no_of_jobs; i++)
    {
        int job_no = i;
        int job_id = proc[i].pid;
        char *job_name = proc[i].name;
        char *job_status = proc[i].stat;
        int job_type = proc[i].type;
        // printf("job_status: %s\n", job_status);
        if (strcmp(job_status, "Running") == 0 && flg_r == 1)
        {
            printf("[%d] %s %s [%d]\n", i, job_status, job_name, job_id);
        }
        else if (strcmp(job_status, "Stopped") == 0 && flg_s == 1)
        {
            printf("[%d] %s %s [%d]\n", i, job_status, job_name, job_id);
        }
        else if (flg_s == 0 && flg_r == 0)
        {
            printf("[%d] %s %s [%d]\n", i, job_status, job_name, job_id);
        }
    }
}

void UPDATE_JOBS()
{
    for (int i = 0; i < no_of_jobs; i++)
    {
        getstatus(i);
    }
}