/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:24:37 by jissa             #+#    #+#             */
/*   Updated: 2025/09/03 19:35:31 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_builtin(char **args, char **env)
{
	int	i;
	int	j;

	if (!args[1])
		return (0);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], args[1], strlen(args[1])) == 0 \
&& env[i][strlen(args[1])] == '=')
		{
			j = i;
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			continue ;
		}
		i++;
	}
	return (0);
}
