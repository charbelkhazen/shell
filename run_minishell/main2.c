/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:36:48 by jissa             #+#    #+#             */
/*   Updated: 2025/09/18 16:17:36 by chkhazen         ###   ########.fr       */
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

void	unclosedquotes(char *input, char ***envp)
{
	int	countquotes;
	int	countdquotes;

	countquotes = 0;
	countdquotes = 0;
	while (*input)
	{
		if (*input == '"')
			countdquotes ++;
		else if (*input == '\'')
			countquotes ++;
		input ++;
	}
	if ((countdquotes % 2) || (countquotes % 2))
	{
		freeenv(*envp);
		printf("Error, quotes should be closed\n");
		exit(1);
	}
}

void	launchprgm(char **input, char **tempinput, char ***envp, int *status)
{
	signal(SIGINT, setsig);
	*input = readline("minishell$ ");
	if (g_globsig == SIGINT)
	{
		g_globsig = 0;
		*status = (130 & 0xFF) << 8;
	}
	*tempinput = *input;
	if (!(*input))
	{
		freeenv(*envp);
		write(1, "exit\n", 5);
		exit(WEXITSTATUS(*status));
	}
	unclosedquotes(*input, envp);
	add_history(*input);
}
