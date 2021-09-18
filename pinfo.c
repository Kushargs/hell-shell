#include "headers.h"

void PINFO(char *arguments[100], int no_of_arguments)
{
    int err = 0;
    int pid;
    if (no_of_arguments == 0)
        pid = P_ID;
    else if (no_of_arguments == 1)
        pid = atoi(arguments[0]);
    else
        printf("to many arguments\n");

    char exe_path[buff_sz];
    sprintf(exe_path, "/proc/%d/exe", pid);

    char status_path[buff_sz];
    sprintf(status_path, "/proc/%d/stat", pid);

    //get address
    char address[buff_sz];
    // printf("exe_path: %s, status_path: %s\n", exe_path, status_path);
    
    err = readlink(exe_path, address, buff_sz);
    if (err < 0)
    {
        perror("readlink");
        return;
    }

    //get process status and memory
    FILE *file = fopen(status_path, "r");
    if (file == NULL)
    {
        perror("fopen");
        return;
    }
    char status;
    int V_memory;

    fscanf(file, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status, &V_memory);


    //PRInting

    printf("pid -- %d\n", pid);
    if(pid == P_ID)
        printf("Process Status -- %c+\n", status);
    else
        printf("Process Status -- %c+\n", status);
    printf("Memory -- %d\n", V_memory);
    printf("Executable_path -- %s\n", address);

    return;


    // printf("path: %s\n",path);
}