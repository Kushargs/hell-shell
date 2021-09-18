#include "headers.h"

void HISTORY(char *argumants[100], int no_of_arguments)
{
    if (no_of_arguments == 0)
    {
        if (history_index_w > 20)
            history_index_r = history_index_w - 20;
        else
            history_index_r = 0;
        for (int i = 0; history_list[history_index_r] == NULL || i < 20; i++)
        {
            if (strcmp(history_list[history_index_r], "") == 0)
                break;

            printf("%s", history_list[history_index_r]);
            history_index_r++;
        }
    }
    else if (no_of_arguments == 1)
    {
        int n = atoi(argumants[0]);
        if (history_index_w > n)
            history_index_r = history_index_w - n;
        else
            history_index_r = 0;
        for (int i = 0; history_list[history_index_r] == NULL || i < 20; i++)
        {
            if (strcmp(history_list[history_index_r], "") == 0)
                break;

            printf("%s", history_list[history_index_r]);
            history_index_r++;
        }
    }
    else
    {
        printf("too many arguments\n");
    }
    
}
