#include "headers.h"

void LS_l(char *directory, int a_flag)
{
    // printf("l_flag: 1, a_flag: %d, directory: %s\n", a_flag, directory);
    errno = 0;
    DIR *dir = opendir(directory);
    if (dir == NULL)
    {
        if (errno == 20)
            printf("%s\n", directory);
        else
            perror("ls");
        return;
    }
    struct dirent *file;
    struct stat status;

    while (1)
    {
        errno = 0;
        char file_name[buff_sz];

        file = readdir(dir);
        if (file == NULL)
        {
            if (errno != 0)
                perror("ls");
            break;
        }
        if (a_flag == 1)
        {
            strcpy(file_name, directory);
            strcat(file_name, "/");
            strcat(file_name, file->d_name);
            stat(file_name, &status);

            printf("%s", (S_ISDIR(status.st_mode)) ? "d" : "-");
            printf("%s", (status.st_mode & S_IRUSR) ? "r" : "-");
            printf("%s", (status.st_mode & S_IWUSR) ? "w" : "-");
            printf("%s", (status.st_mode & S_IXUSR) ? "x" : "-");
            printf("%s", (status.st_mode & S_IRGRP) ? "r" : "-");
            printf("%s", (status.st_mode & S_IWGRP) ? "w" : "-");
            printf("%s", (status.st_mode & S_IXGRP) ? "x" : "-");
            printf("%s", (status.st_mode & S_IROTH) ? "r" : "-");
            printf("%s", (status.st_mode & S_IWOTH) ? "w" : "-");
            printf("%s", (status.st_mode & S_IXOTH) ? "x" : "-");
            printf(" %ld ", status.st_nlink);

            struct group *grp;
            struct passwd *user;
            grp = getgrgid(status.st_gid);
            user = getpwuid(status.st_uid);
            printf("%s ", grp->gr_name);
            printf("%s ", user->pw_name);

            printf("%ld\t", status.st_size);

            char samay[buff_sz];
            strftime(samay, buff_sz, "%h %d %H:%M", localtime(&status.st_mtime));
            printf("%s ", samay);

            printf("%s\n", file->d_name);
        }
        else
        {
            if (file->d_name[0] != '.')
            {
                strcpy(file_name, directory);
                strcat(file_name, "/");
                strcat(file_name, file->d_name);
                stat(file_name, &status);

                printf("%s", (S_ISDIR(status.st_mode)) ? "d" : "-");
                printf("%s", (status.st_mode & S_IRUSR) ? "r" : "-");
                printf("%s", (status.st_mode & S_IWUSR) ? "w" : "-");
                printf("%s", (status.st_mode & S_IXUSR) ? "x" : "-");
                printf("%s", (status.st_mode & S_IRGRP) ? "r" : "-");
                printf("%s", (status.st_mode & S_IWGRP) ? "w" : "-");
                printf("%s", (status.st_mode & S_IXGRP) ? "x" : "-");
                printf("%s", (status.st_mode & S_IROTH) ? "r" : "-");
                printf("%s", (status.st_mode & S_IWOTH) ? "w" : "-");
                printf("%s", (status.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %ld ", status.st_nlink);

                struct group *grp;
                struct passwd *user;
                grp = getgrgid(status.st_gid);
                user = getpwuid(status.st_uid);
                printf("%s ", grp->gr_name);
                printf("%s ", user->pw_name);

                printf("%ld\t", status.st_size);

                char samay[buff_sz];
                strftime(samay, buff_sz, "%h %d %H:%M", localtime(&status.st_mtime));
                printf("%s ", samay);

                printf("%s\n", file->d_name);
            }
        }
    }

    return;
}

void LS_nl(char *directory, int a_flag)
{
    // printf("l_flag: 0, a_flag: %d, directory: %s\n", a_flag, directory);
    errno = 0;
    DIR *dir = opendir(directory);
    if (dir == NULL)
    {
        if (errno == 20)
            printf("%s\n", directory);
        else
            perror("ls");
        return;
    }
    struct dirent *file;
    while (1)
    {
        errno = 0;
        file = readdir(dir);
        if (file == NULL)
        {
            if (errno != 0)
                perror("ls");
            break;
        }
        if (a_flag == 1)
            printf("%s  ", file->d_name);
        else
        {
            if (file->d_name[0] != '.')
                printf("%s  ", file->d_name);
        }
    }
    printf("\n");
    closedir(dir);
    return;
}

void LS(char *arguments[100], int no_of_arguments)
{
    // find flags and directories
    int l_flag = 0;
    int a_flag = 0;
    int no_of_directorys = 0;
    char directorys[100][buff_sz];
    // printf("inside ls\n");
    for (int i = 0; i < no_of_arguments; i++)
    {
        if (strcmp(arguments[i], "-l") == 0)
            l_flag = 1;
        else if (strcmp(arguments[i], "-a") == 0)
            a_flag = 1;
        else if (strcmp(arguments[i], "-al") == 0)
        {
            l_flag = 1;
            a_flag = 1;
        }
        else if (strcmp(arguments[i], "-la") == 0)
        {
            l_flag = 1;
            a_flag = 1;
        }
        else
        {
            strcpy(directorys[no_of_directorys], arguments[i]);
            no_of_directorys++;
        }
    }

    if (no_of_directorys == 0)
    {
        if (l_flag == 0)
            LS_nl(".", a_flag);
        else
            LS_l(".", a_flag);
    }

    for (int i = 0; i < no_of_directorys; i++)
    {
        char address[buff_sz];
        if (directorys[i][0] == '~')
        {
            char path_temp[buff_sz];
            strcpy(address, HOME);
            strcat(address, directorys[i] + 1);
            if (no_of_directorys > 1)
                printf("%s\n", address);
            if (l_flag == 0)
                LS_nl(address, a_flag);
            else
                LS_l(address, a_flag);
        }
        else
        {
            strcpy(address, directorys[i]);
            if (no_of_directorys > 1)
                printf("%s:\n", address);
            if (l_flag == 0)
                LS_nl(address, a_flag);
            else
                LS_l(address, a_flag);
        }
    }

    // function without l
}