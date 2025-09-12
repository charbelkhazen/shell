/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:23:15 by jissa             #+#    #+#             */
/*   Updated: 2025/09/12 11:12:37 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	printpathfromenv(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
		{
			printf("%s\n", ft_strchr(envp[i], '=') + 1);
			return (0);
		}
		i++;
	}
	printf("Could not find path\n");
	return (1);
}

int	pwd(char **args, char **envp)
{
	char	path[1024];

	(void)args;
	if (!getcwd(path, sizeof(path)))
		return (printpathfromenv(envp));
	else
		printf("%s\n", path);
	return (0);
}
