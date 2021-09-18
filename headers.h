#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

int errno;

#define buff_sz 9999
int P_ID; 

char HOME[buff_sz];
char PREV_PATH[buff_sz];
char PATH[buff_sz];

void prompt();
void parser(char *line, char command_array[][1000], int *no_of_commands, char *delimiter);
void execute(char *command);
void LS();
void CD(char *arguments[100], int no_of_arguments);
void PWD();
void ECHO();
void LS(char *arguments[100], int no_of_arguments);
void OTHER_COMMAND(char* command, char* argumants[100], int no_of_arguments);
void PINFO(char* arguments[100], int no_of_arguments);

void child_died(int signal);