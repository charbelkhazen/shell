/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:35:06 by jissa             #+#    #+#             */
/*   Updated: 2025/09/10 17:36:40 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	main(int argc, char *argv[], char **envp)
{
	char	*input;
	t_tree	*result;
	int		status;
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
			continue ;
		}
		result = parseprogram(&input, status);
		executeprgm(result, &env, &status);
		cleanexitexec(status, result, tempinput);
	}
	rl_clear_history();
}
