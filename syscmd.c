
#include "headers.h"



void CD(char *arguments[100], int no_of_arguments)
{
    if (no_of_arguments == 0)
        chdir(HOME);
    else if (no_of_arguments == 1)
    {
        if (arguments[0][0] == '~')
        {
            char path_temp[buff_sz];
            strcpy(path_temp, HOME);
            strcat(path_temp, arguments[0] + 1);
            if(chdir(path_temp) != 0){perror("cd");}
            strcpy(PREV_PATH, PATH);
            strcpy(PATH, path_temp);
        }
        else if (arguments[0][0] == '-')
        {
            if(chdir(PREV_PATH) != 0){perror("cd");}
            printf("%s\n", PREV_PATH);
            char TEMP_path[buff_sz];
            strcpy(TEMP_path, PREV_PATH);
            strcpy(PREV_PATH, PATH);
            strcpy(PATH, TEMP_path);

        }
        else 
        {
            char temp_path[buff_sz];
            strcpy(temp_path, arguments[0]);
            if(chdir(temp_path) != 0){perror("cd");}
            strcpy(PREV_PATH, PATH);
            getcwd(PATH, buff_sz);
        }
        
    }
    else{
        printf("Too many arguments\n");
    }
    return;
}


void PWD()
{
    printf("%s\n", PATH);
}


void ECHO(char* arguments[100], int no_of_arguments)
{
    for (int i = 0; i < no_of_arguments; i++)
        printf("%s ", arguments[i]);

    printf("\n");
}


