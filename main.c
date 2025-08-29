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

void	update_shlvl_on_start(char **my_env)
{
	int		i = 0;
	int		value;
	char	*new_value;
	char	*tmp;

	while (my_env[i])
	{
		if (ft_strncmp(my_env[i], "SHLVL=", 6) == 0)
		{
			value = ft_atoi(my_env[i] + 6);
			value++;
			tmp = ft_itoa(value);
			my_env[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
			return ;
		}
		i++;
	}
	my_env[i] = ft_strdup("SHLVL=1");
	my_env[i + 1] = NULL;
}

void	update_shlvl_on_exit(char **my_env)
{
	int		i = 0;
	int		value;
	char	*new_value;
	char	*tmp;

	while (my_env[i])
	{
		if (ft_strncmp(my_env[i], "SHLVL=", 6) == 0)
		{
			value = ft_atoi(my_env[i] + 6);
			value--;
			if (value < 0)
				value = 0;
			tmp = ft_itoa(value);
			my_env[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
			return ;
		}
		i++;
	}
}

int main(int argc, char *argv[], char **envp)
{
	char	*input;
	t_tree	*result;
	int	pid;
	int	status;
	char	*tempinput;

	signal(SIGQUIT, SIG_IGN);
	status = 0;
	update_shlvl_on_start(envp);
	while (1)
	{
		signal(SIGINT, setsig);
		input = readline("minishell$ ");
		tempinput = input;
		if (!input)
		{
			write(1, "exit\n", 5);
			update_shlvl_on_exit(envp);
			return (0);
		}
		add_history(input);
		if (startbuiltin(input))
		{
			applybuiltin(input, envp);
			continue;
		}
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
		freetree(result);
		free(tempinput);
	}
}
