#include "headers.h"

void PIPE(char *command)
{

    char **commands;
    commands = malloc(100 * sizeof(char *));
    int index = 0;
    char *temp = strtok(command, "|");

    while (temp != NULL)
    {
        commands[index] = temp;
        temp = strtok(NULL, "|");
        index++;
    }

    int p[2];
    int fd = 0;
    int stdin = dup(0), stdout = dup(1);

    for (int i = 0; i < index; i++)
    {

        pipe(p);
        pid_t pid = fork();
        
        if (pid == 0)
        {
            dup2(fd, 0);
            if(i != index -1)
                dup2(p[1], 1);
            close(p[0]);
            execute(commands[i]);
            exit(1);
        }
        else
        {
            wait(NULL);
            fd = p[0];
            close(p[1]);
        }
    }



}