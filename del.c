#include "minishell.h"

int main(int ac, char *arg[], char *env[])
{
        int             pipefd[2];
        pid_t   pid1;
        pid_t   pid2;
	int *status;

        pipe(pipefd);
        pid1 = fork();
        if (pid1 == 0)
        {
                dup2(pipefd[1], 1); 
                close(pipefd[0]);
                close(pipefd[1]);
		write(2, "1\n", 2);
		execve("/bin/cat", arg, env);
		write(2, "2\n", 2);
        }
	write(2, "3\n", 2);
        pid2 = fork();
        if (pid2 == 0)
        {
                dup2(pipefd[0], 0); 
                close(pipefd[0]);
                close(pipefd[1]);
		write(2, "4\n", 2);
		execve("/bin/cat", arg, env);
        }
	write(2, "5\n", 2);
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid1, status, 0); 
        waitpid(pid2, status, 0); 
}
