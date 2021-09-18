#include "headers.h"

void parser(char* line, char command_array[][1000], int* no_of_commands, char* delimiter)
{
    char* command = strtok(line, delimiter);
    int command_no = 0;
    
    while(command != NULL )
    {
        strcpy(command_array[command_no], command);
        command = strtok(NULL, delimiter);
        command_no++;
    }
    
    *no_of_commands = command_no;

}
