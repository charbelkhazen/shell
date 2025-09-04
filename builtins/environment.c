/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:20:53 by jissa             #+#    #+#             */
/*   Updated: 2025/09/03 19:35:00 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	environment(char **args, char **env)
{
	int	j;

	j = 0;
	if (args[1])
	{
		perror("No such file or directory");
		return (127);
	}
	while (env[j])
	{
		printf("%s\n", env[j]);
		j++;
	}
	return (0);
}
