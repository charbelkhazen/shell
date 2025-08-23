#include "minishell.h"

char	globsig = 0;

void    setsig(int sig)
{
	(char) sig;
	rl_on_new_line();
	rl_on_new_line(); 
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(int argc, char *argv[], char **envp)
{
	char	*input;
	t_tree	*result;
	int	pid;
	int	status;

	if (!globsig)
		signal(SIGINT, setsig);
	signal(SIGINT, SIG_IGN);
	status = 0;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		add_history(input);
		if (isexit(input))
			applyexit(input);
		result = parseprogram(&input, WEXITSTATUS(status));
		pid = fork();
		if (!pid)
			trav_tree(result, envp, &status);
		wait(&status);
		//clearhistory?
	}
}
