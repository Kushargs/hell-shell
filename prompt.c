#include "headers.h"

void prompt() {

    // get user_name and system name 
    char username[100];
    char systemname[100];

    getlogin_r(username, 100);
    gethostname(systemname, 100);

    char tem_path[buff_sz];
    char PATH_display[buff_sz];

    char buffer[buff_sz];

    getcwd(buffer, buff_sz);
    strcpy(tem_path, buffer);

    int index;
    for(index = 0; index < strlen(HOME); index++)
    {
        if(HOME[index] != tem_path[index])
            break;
    }


    if (index == strlen(HOME))
    {
        strcpy(PATH_display, "~");
        strcat(PATH_display, tem_path+index);
    }
    else
    {
        strcpy(PATH_display, tem_path);
    }
    // printf("PATH: %s, HOME: %s, PREVPATH %s", PATH, HOME, PREV_PATH);
    printf("%s@%s:%s>", username, systemname, PATH_display);    
}
