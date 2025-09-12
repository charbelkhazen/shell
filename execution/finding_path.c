/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:13:58 by jissa             #+#    #+#             */
/*   Updated: 2025/09/12 11:32:10 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **path_splitted, int index)
{
	while (path_splitted[index])
		free(path_splitted[index++]);
	free(path_splitted);
}

char	*get_path(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*join_and_check(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*search_in_path(char **path_splitted, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (path_splitted[i])
	{
		full_path = join_and_check(path_splitted[i], cmd);
		if (full_path)
			return (full_path);
		i++;
	}
	return (NULL);
}

char	*find_full_path(char *command, char *path)
{
	char	**path_splitted;
	char	*full_path;
	char	*cwd;
	char	*temp;

	path_splitted = ft_split(path, ':');
	full_path = search_in_path(path_splitted, command);
	free_split(path_splitted, 0);
	if (full_path)
		return (full_path);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (0);
	temp = ft_strjoin(cwd, "/");
	free(cwd);
	full_path = ft_strjoin(temp, command);
	free(temp);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}
