/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:22:03 by jissa             #+#    #+#             */
/*   Updated: 2025/09/03 19:35:04 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_builtin(char **args)
{
	long long	status;
	int			g_exit_status;

	g_exit_status = 0;
	write(1, "exit\n", 5);
	if (!args[1])
		exit (g_exit_status);
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
	status = ft_atoll(args[1]);
	exit ((unsigned char)status);
	return ((unsigned char)status);
}
