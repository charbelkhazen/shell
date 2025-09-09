/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:22:03 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 13:51:08 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_builtin(char **args, char **env)
{
	long long	status;
	int			g_exit_status;

	g_exit_status = 0;
	write(1, "exit\n", 5);
	if (!args[1])
	{
		rl_clear_history();
		freeenv(env);
		free_args(args);
		exit(g_exit_status);
	}
	if (!is_numeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		return (2);
	}
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	rl_clear_history();
	status = ft_atoll(args[1]);
	freeenv(env);
	free_args(args);
	exit ((unsigned char)status);
	return ((unsigned char)status);
}
