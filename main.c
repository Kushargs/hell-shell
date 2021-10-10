#include "headers.h"

int no_of_jobs = 0;
struct Proc proc[100];


int main()
{

    getcwd(HOME, buff_sz);
    strcpy(PREV_PATH, HOME);
    strcpy(PATH, HOME);
    history_index_r = 0;
    history_index_w = 0;
    
    while (1)
    {
        // INITIAL PROMPT
        P_ID = getpid();


        signal(SIGCHLD, child_died);
        signal(SIGINT, SIG_IGN);
        signal(SIGTSTP, ctrl_Z);

        prompt();

        // GET INTPUT
        size_t line_sz = 0;
        char *input = (char *)malloc(line_sz * sizeof(char));
        int read_sz = getline(&input, &line_sz, stdin);
        if(read_sz == -1)
        {
            break;
        }

        // Parse the line read
        char commands[100][1000];
        int no_of_commands;
        if (read_sz == 1)
            continue;
        parser(input, commands, &no_of_commands, ";");

        // EXECUTE THE COMMANDS

        for (int i = 0; i < no_of_commands; i++)
        {
            strcpy(history_list[history_index_w], commands[i]);
            execute(commands[i]);
            history_index_w++;
        }
    }
}
