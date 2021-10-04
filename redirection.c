#include "headers.h"

void REDIRECT(char *command, int in_dir, int out_dir, int out_dir_a)
{
    char *output_file;
    char *input_file;
    char *the_command;
    the_command = (char *)malloc(buff_sz * sizeof(char));

    strcpy(the_command, command);

    int stdin = dup(0), stdout = dup(1);

    // printf("command:%s\n in_dir: %d\n out_dir:%d\n", command, in_dir, out_dir);

    if (out_dir == 1)
    {
        the_command = strtok(the_command, ">");
        output_file = strtok(NULL, ">");
        output_file = strtok(output_file, " \r\t\n");
    }
    else if (out_dir_a == 1)
    {
        the_command = strtok(the_command, ">>");
        output_file = strtok(NULL, ">>");
        output_file = strtok(output_file, " \r\t\n");
    }

    if (in_dir == 1)
    {
        the_command = strtok(the_command, "<");
        input_file = strtok(NULL, "<");
        input_file = strtok(input_file, " \r\t\n");
    }

    // the_command = strtok(the_command, " \r\t\n");

    pid_t pid = fork();

    if (pid == 0)
    {
        if (in_dir)
        {
            int input_fd = open(input_file, O_RDONLY);
            if (input_fd < 0)
            {
                perror("input");
                return;
            }

            dup2(input_fd, 0);
        }

        if (out_dir || out_dir_a)
        {
            int out_fd;
            if (out_dir == 1)
                out_fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            else if (out_dir_a == 1)
                out_fd = open(output_file, O_CREAT | O_WRONLY | O_APPEND, 0644);

            if (out_fd < 0)
            {
                perror("Output Redirection");
                return;
            }

            dup2(out_fd, 1);
        }
        // printf("command:%s\n", the_command);

        execute(the_command);
        // printf("command:%s\n", the_command);

        dup2(stdin, 0), dup2(stdout, 1);
    }
    else
    {
        waitpid(pid, NULL, 0);
        dup2(stdin, 0), dup2(stdout, 1);
    }
}