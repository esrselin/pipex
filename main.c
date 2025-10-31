#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int ac, char *av[])
{
    (void) ac;
    (void) av;
    int infd, outfd;
    int fd[2];
    int pid;

    infd = open("infile.txt", O_RDONLY);
    outfd = open("outfile.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    pipe(fd);
    pid = fork();

    if(pid == 0)
    {
        
        dup2(infd,1);
        close(fd[1]);
        execve("/usr/bin/grep", ...)
    }
    else
    {
        dup2(fd[1], 0);
        close(fd[0]);
        execve("/usr/bin/grep", ...)
    }

close(fd[0]);
close(fd[1]);

waitpid(pid, NULL, 0);
}