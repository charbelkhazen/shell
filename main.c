#include "minishell.h"

int	globsig = 0;

void    setsig(int sig)
{
	globsig = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line(); 
	rl_redisplay();
}

int main(int argc, char *argv[], char **envp)
{
	char	*input;
	t_tree	*result;
	int	pid;
	int	status;

	signal(SIGQUIT, SIG_IGN);
	status = 0;
	while (1)
	{
		signal(SIGINT, setsig);
		input = readline("minishell$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		add_history(input);
		if (isexit(input))
			applyexit(input);
		result = parseprogram(&input, status);
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (!pid)
		{
			signal(SIGINT, SIG_DFL);
			trav_tree(result, envp, &status);
		}
		wait(&status);
		if (!(WIFEXITED(status)) && (WTERMSIG(status) == SIGINT))
			write(1, "\n", 2);
		//clearhistory?
	}
}
