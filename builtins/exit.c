/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:22:03 by jissa             #+#    #+#             */
/*   Updated: 2025/09/14 21:01:43 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	onlyexit(char **args, char **env, int startflag, int oldstatus)
{
	rl_clear_history();
	freeenv(env);
	if (startflag)
		free_args(args);
	exit(WEXITSTATUS(oldstatus));
}

int	exit_builtin(char **args, char **env, int startflag, int oldstatus)
{
	long long	status;

	if (startflag)
		write(1, "exit\n", 5);
	if (!args[1])
		onlyexit(args, env, startflag, oldstatus);
	if (!is_numeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		exit(1);
	}
	rl_clear_history();
	status = ft_atoll(args[1]);
	freeenv(env);
	if (startflag)
		free_args(args);
	exit ((unsigned char)status);
	return ((unsigned char)status);
}
