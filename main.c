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
	int		i;
	int		value;
	char	*new_value;
	char	*tmp;
	char	*othertemp;

	i = 0;
	while (my_env[i])
	{
		if (ft_strncmp(my_env[i], "SHLVL=", 6) == 0)
		{
			value = ft_atoi(my_env[i] + 6);
			value++;
			tmp = ft_itoa(value);
			othertemp = my_env[i];
			my_env[i] = ft_strjoin("SHLVL=", tmp);
			free(othertemp);
			free(tmp);
			return ;
		}
		i++;
	}
}

void	basicsetup(int *status, char **envp)
{
	rl_change_environment = 0;
	signal(SIGQUIT, SIG_IGN);
	*status = 0;
	update_shlvl_on_start(envp);
}

void	launchprgm(char **input, char **tempinput, char ***envp)
{	
	signal(SIGINT, setsig);
	*input = readline("minishell$ ");
	*tempinput = *input;
	if (!(*input))
	{
		freeenv(*envp);
		write(1, "exit\n", 5);
		exit(0);
	}
	add_history(*input);
}

void	handlestartbuiltin(char *input, char ***envp, int *status)
{
	*status = applybuiltin(input, envp, *status);
	*status = (*status & 0xFF) << 8;
}
	
void	setupinchild(t_tree *result)
{
	if (!result)
		exit(2);
	signal(SIGINT, SIG_DFL);
}

void	executeprgm(t_tree *result, char ***envp, int *status)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		setupinchild(result);
		trav_tree(result, envp, status);
	}
	wait(status);
}

void	cleanexitexec(int status, t_tree *result, char *tempinput)
{
	if (!(WIFEXITED(status)) && (WTERMSIG(status) == SIGINT))
		write(1, "\n", 2);
	if (result)
		freetree(result);
	free(tempinput);
}

int main(int argc, char *argv[], char **envp)
{
	char	*input;
	t_tree	*result;
	int	status;
	char	*tempinput;
	char	**env;

	env = dupenv(envp);
	basicsetup(&status, env);
	while (1)
	{
		launchprgm(&input, &tempinput, &env);
		if (startbuiltin(input))
		{
			handlestartbuiltin(input, &env, &status);
			free(input);
			continue;
		}
		result = parseprogram(&input, status);
		executeprgm(result, &env, &status);
		cleanexitexec(status, result, tempinput);
	}
	rl_clear_history();
}
