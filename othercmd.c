#include "headers.h"

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
            printf("[%d]\n",child_id);
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
            int err = waitpid(-1, NULL, WUNTRACED);
            if (err < 0)
            {
                perror("waitpid");
            }

            return;
        }

    }
}