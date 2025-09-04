/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:20:12 by jissa             #+#    #+#             */
/*   Updated: 2025/09/03 19:34:42 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(char **my_env, char *str, int size)
{
	char	path[1024];
	int		i;

	i = 0;
	if (getcwd(path, sizeof(path)) == NULL)
		return ;
	while (my_env[i])
	{
		if (ft_strncmp(my_env[i], str, size) == 0)
		{
			my_env[i] = ft_strjoin(str, path);
			return ;
		}
		i++;
	}
}

char	*check_home(char **args)
{
	char	*target;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		target = getenv("HOME");
		if (!target)
		{
			printf("minishell: cd: HOME not set\n");
			return (NULL);
		}
		return (target);
	}
	return (NULL);
}

char	*check_absolute_home(char **args, char *path, size_t size)
{
	char	*home;

	if (args[1][0] == '~' && args[1][1] == '/')
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("minishell: cd: HOME not set\n");
			return (NULL);
		}
		ft_strlcpy(path, home, size);
		ft_strlcat(path, args[1] + 1, size);
		return (path);
	}
	return (NULL);
}

int	change_directory(char **args, char **env)
{
	char	path[1024];
	char	*target;

	update_pwd(env, "OLDPWD=", 7);
	target = check_home(args);
	if (target == NULL && (!args[1] || ft_strcmp(args[1], "~") == 0))
		return (1);
	if (!target)
	{
		target = check_absolute_home(args, path, sizeof(path));
		if (target == NULL && args[1] && args[1][0] == '~' && args[1][1] == '/')
			return (1);
	}
	if (!target)
		target = args[1];
	if (chdir(target) == -1)
	{
		perror("cd");
		return (1);
	}
	update_pwd(env, "PWD=", 4);
	return (0);
}
