/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:36:48 by jissa             #+#    #+#             */
/*   Updated: 2025/09/12 12:00:19 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_globsig = 0;

void	setsig(int sig)
{
	g_globsig = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	update_shlvl_on_start(char ***my_env)
{
	int		i;
	int		value;
	char	*tmp;
	char	*othertemp;

	i = 0;
	while (*(*my_env + i))
	{
		if (ft_strncmp(*(*my_env + i), "SHLVL=", 6) == 0)
		{
			value = ft_atoi(*(*my_env + i) + 6);
			value++;
			tmp = ft_itoa(value);
			othertemp = *(*my_env + i);
			*(*my_env + i) = ft_strjoin("SHLVL=", tmp);
			free(othertemp);
			free(tmp);
			return ;
		}
		i++;
	}
	addinenv("SHLVL=1", my_env);
}

void	basicsetup(int *status, char ***envp)
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
