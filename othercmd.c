#include "headers.h"
extern int no_of_jobs;
extern struct Proc proc[100];

void OTHER_COMMAND(char *command, char *argumants[100], int no_of_arguments)
{
    int bg_flag = 0;
    int index = 1;
    int shell_id = getpid();
    char *args[100] = {NULL};
    args[0] = malloc(100 * sizeof(char));

    strcpy(args[0], command);
    for (int i = 0; i < no_of_arguments; i++)
    {
        if (strcmp(argumants[i], "&") == 0)
            bg_flag = 1;
        else
        {
            args[index] = strdup(argumants[i]);
            // printf("args:%s", args[index] );
            // strcpy(args[index], argumants[i]);
            index++;
        }
    }
    pid_t child_id = fork();
    int p_id = getpid();

    //BACKGROUND
    if (bg_flag == 1)
    {
        int err;
        err = setpgid(0, 0);
        if (err < 0)
        {
            perror("error");
            return;
        }

        if (child_id == -1)
            perror("incompetent");
        else if (child_id == 0)
        {

            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);

            err = execvp(command, args);
            if (err < 0)
            {
                perror("erecvp");
                return;
            }

            exit(0);
        }
        else
        {
            proc[no_of_jobs].pid = child_id;
            proc[no_of_jobs].name = args[0];
            getstatus(no_of_jobs);
            proc[no_of_jobs].type = 1;
            no_of_jobs++;
            // printf("no_of_jobs: %d\n",  no_of_jobs);
            // printf("name: %s\n", proc[no_of_jobs].name );

            printf("[%d]\n", child_id);
            return;
        }
    }
    //FOREGROUND

    else
    {
        int err;

        if (child_id == -1)
            perror("incompetent");
        else if (child_id == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);
            signal(SIGTTIN, SIG_DFL);
            err = execvp(command, args);
            if (err < 0)
            {
                perror("erecvp");
                return;
            }
            exit(0);
        }
        else
        {
            proc[no_of_jobs].pid = child_id;
            proc[no_of_jobs].name = args[0];
            getstatus(no_of_jobs);
            proc[no_of_jobs].type = 0;
            no_of_jobs++;
            // printf("no_of_jobs: %d\n",  no_of_jobs);
            // printf("name: %s\n", proc[no_of_jobs].name );

            while (waitpid(child_id, NULL, WUNTRACED) > 0)
                break;

            signal(SIGINT, SIG_IGN);

            // if (err < 0)
            // {
            //     perror("waitpid");
            // }

            return;
        }
    }
}
