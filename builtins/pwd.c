/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:23:15 by jissa             #+#    #+#             */
/*   Updated: 2025/09/10 18:57:01 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(char **args, char **envp)
{
	char	path[1024];
	int		i;

	(void)args;
	i = 0;
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
