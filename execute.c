#include "headers.h"

void get_command_arguments(char *command, char command_name[buff_sz], char *argument[100], int *no_of_arguments)
{
    char *token = strtok(command, " \n\r\t");
    int index = 0;
    strcpy(command_name, token);
    // printf("command_name_in_fun: %s\n", command_name);

    token = strtok(NULL, " \n\r\t");

    while (token != NULL)
    {
        argument[index] = token;
        token = strtok(NULL, " \n\r\t");
        index++;
    }

    *no_of_arguments = index;

    // printf("command: %s\n", command_name);

    // for(int i = 0; i < index; i++)
    // {
    //     printf("argument: %s\n", argument[i]);
    // }
}

void execute(char *command)
{
    char command_name[buff_sz];
    char *argument[100];
    int no_of_arguments;

    get_command_arguments(command, command_name, argument, &no_of_arguments);
    // printf("command name: -%s-, argumants: %s\n", command_name, argument[0]);
    if (strcmp(command_name, "ls") == 0)
        LS(argument, no_of_arguments);
    else if (strcmp(command_name, "cd") == 0)
    {
        // printf("command: cd, arguments1: %s \n", argument[0]);
        CD(argument, no_of_arguments);
    }
    else if (strcmp(command_name, "pwd") == 0)
    {
        PWD();
    }
    else if (strcmp(command_name, "echo") == 0)
    {
        ECHO(argument, no_of_arguments);
    }
    else if (strcmp(command_name, "pinfo") == 0)
    {
        PINFO(argument, no_of_arguments);
    }
    else if (strcmp(command_name, "repeat") == 0)
    {
        char temp[buff_sz];
        strcpy(temp, argument[1]);
        for (int i = 2; i < no_of_arguments; i++)
        {
            strcat(temp, " ");
            strcat(temp, argument[i]);
        }
        int repeat_no = atoi(argument[0]);
        for (int i = 0; i < repeat_no; i++)
        {
            char temp2[buff_sz];
            strcpy(temp2, temp);
            execute(temp2);
        }
    }
    else
    {
        OTHER_COMMAND(command_name, argument, no_of_arguments);
    }
}