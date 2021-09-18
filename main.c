#include "headers.h"

int main()
{

    getcwd(HOME, buff_sz);
    strcpy(PREV_PATH, HOME);
    strcpy(PATH, HOME);

    while (1)
    {
        // INITIAL PROMPT
        signal(SIGCHLD, child_died);

        prompt();
        P_ID = getpid();

        // GET INTPUT
        size_t line_sz = 0;
        char *input = (char *)malloc(line_sz * sizeof(char));
        int read_sz = getline(&input, &line_sz, stdin);
        
        // Parse the line read
        char commands[100][1000];
        int no_of_commands;
        if (read_sz == 1)
            continue;
        parser(input, commands, &no_of_commands, ";");

        // EXECUTE THE COMMANDS
        
        for (int i = 0; i < no_of_commands; i++)
            execute(commands[i]);
    }
}
