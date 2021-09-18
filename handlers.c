#include "headers.h"

void child_died(int signal)
{

    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);

    if (pid < 0)
        perror("child_died");
    else
    {

        if (WIFEXITED(status))
        {
            fprintf(stderr, "\npid: %d exited normally, status = %d\n", pid, WEXITSTATUS(status));

        return;
    }
}
}
