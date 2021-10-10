#include "headers.h"

void REPLAY(char *argument[100], int no_of_arguments)
{
    int interval, period;
    char command_r[100];
    // printf("command: %s\n", command_r);

    for (int i = 1; i < no_of_arguments; i++)
    {
        // printf("argument: %s\n", argument[i]);
        if (strcmp(argument[i], "replay") == 0)
            continue;
        else if (strcmp(argument[i], "-command") == 0)
            continue;
        else if (strcmp(argument[i], "-interval") == 0)
        {
            interval = atoi(argument[i + 1]);
            i++;
        }
        else if (strcmp(argument[i], "-period") == 0)
        {
            period = atoi(argument[i + 1]);
            i++;
        }
        else
        {
            strcat(command_r, " ");
            strcat(command_r, argument[i]);
        }
    }

    int count = period / interval;
    // printf("i am here\n");

    // int pid = fork();
    for (int i = 0; i < count; i++)
    {
        sleep(interval);
        execute(command_r);
    }

    // printf("command: -%s-, interval: %d, period: %d\n", command_r, interval, period);
}