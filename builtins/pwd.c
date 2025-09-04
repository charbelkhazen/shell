/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:23:15 by jissa             #+#    #+#             */
/*   Updated: 2025/09/03 19:35:26 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(char **args, char **envp)
{
	char	path[1024];
	int		i;

	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("getcwd failed");
		return (127);
	}
	else
	{
		while (envp[i])
		{
			if (ft_strcmp(envp[i], "PWD"))
				envp[i] = ft_strdup(path);
			i++;
		}
		printf("%s\n", path);
	}
	return (0);
}
