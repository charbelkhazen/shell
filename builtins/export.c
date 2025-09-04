/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:35:16 by jissa             #+#    #+#             */
/*   Updated: 2025/09/03 19:45:48 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_exportcmd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

char	*create_new_env_var(char *arg, char **var_name)
{
	char	*var_value;
	char	*new_env_var;

	var_value = ft_strchr(arg, '=');
	*var_name = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(var_value));
	new_env_var = ft_strjoin(*var_name, var_value);
	return (new_env_var);
}

int	update_existing_env(char **envp, char *var_name, char *new_env_var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(var_name, envp[i], ft_strlen(var_name)) == 0
			&& envp[i][ft_strlen(var_name)] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(new_env_var);
			return (1);
		}
		i++;
	}
	return (0);
}

void	add_new_env_var(char **envp, char *new_env_var)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = ft_strdup(new_env_var);
	envp[i + 1] = NULL;
}

int	export_builtin(char **args, char **envp)
{
	char	*var_name;
	char	*new_env_var;
	int		found;

	if (!args[1] || !ft_strchr(args[1], '='))
	{
		handle_exportcmd(envp);
		return (1);
	}
	new_env_var = create_new_env_var(args[1], &var_name);
	found = update_existing_env(envp, var_name, new_env_var);
	if (!found)
		add_new_env_var(envp, new_env_var);
	free(var_name);
	free(new_env_var);
	return (0);
}
