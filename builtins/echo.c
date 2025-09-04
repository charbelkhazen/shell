/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:20:38 by jissa             #+#    #+#             */
/*   Updated: 2025/09/03 19:34:55 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_n_flags(char *input)
{
	int	i;

	i = 0;
	if (input[i] != '-' || input[i + 1] != 'n')
		return (0);
	i++;
	while (input[i] == 'n')
		i++;
	if (input[i] != ' ' && input[i] != '\0')
		return (0);
	return (1);
}

int	echo(char **args)
{
	int		i;
	int		j;
	int		no_newline;

	i = 1;
	no_newline = 0;
	while (args[i] && only_n_flags(args[i]))
	{
		no_newline = 1;
		i++;
	}
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			write(1, &args[i][j++], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!no_newline)
		write(1, "\n", 1);
	return (0);
}
