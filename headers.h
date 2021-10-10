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
#include <fcntl.h>

int errno;

#define buff_sz 9999
int P_ID;

char HOME[buff_sz];
char PREV_PATH[buff_sz];
char PATH[buff_sz];

char history_list[100][buff_sz];
int history_index_r;
int history_index_w;

void prompt();
void parser(char *line, char command_array[][1000], int *no_of_commands, char *delimiter);
void execute(char *command);
void LS();
void CD(char *arguments[100], int no_of_arguments);
void PWD();
void ECHO();
void LS(char *arguments[100], int no_of_arguments);
void OTHER_COMMAND(char *command, char *argumants[100], int no_of_arguments);
void PINFO(char *arguments[100], int no_of_arguments);
void HISTORY();
void child_died(int signal);
void JOBS(char *arguments[100], int no_of_arguments);

void REDIRECT(char *command, int in_dir, int out_dir, int out_dir_a);
void PIPE(char *command);
void getstatus(int i);
void UPDATE_JOBS();
void SIG(char *argumants[100], int no_of_arguments);
void FG(char *argumants[100], int no_of_arguments);
void BG(char *argumants[100], int no_of_arguments);
void REPLAY(char* arguments[100], int no_of_arguments);


void ctrl_Z();




struct Proc
{
    int pid;
    char *name;
    char *stat;
    int type;
};
