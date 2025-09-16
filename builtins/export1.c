/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:44:55 by chkhazen          #+#    #+#             */
/*   Updated: 2025/09/15 17:24:51 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_envp(char **envp)
{
	int	i;
	int	j;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char	*quoted_value(char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin("\"", value);
	res = ft_strjoin(tmp, "\"");
	free(tmp);
	return (res);
}

void	add_quotes(char **envp)
{
	int	i;
	char	*value;
	char	*new_entry;
	char	*final_value;
	char	*extracted_var;

	i = 0;
	while (envp[i])
	{
		value = ft_strchr(envp[i], '=');
		if (value)
		{
			extracted_var = ft_substr(envp[i], 0, (ft_strlen(envp[i]) - ft_strlen(value)) + 1);
			final_value = quoted_value(value + 1);
			new_entry = ft_strjoin(extracted_var, final_value);
			free(extracted_var);
			free(final_value);
			free(envp[i]);
			envp[i] = new_entry;
		}
		i++;
	}
}

void	handle_exportcmd(char **envp)
{
	int	i;

	i = 0;
	sort_envp(envp);
	add_quotes(envp);
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

int	validatearg(char *arg)
{
	if (!arg)
		return (0);
	if ((*arg != '_') && (!ft_isalpha(*arg)))
		return (0);
	while (*arg && (*arg != '='))
	{
		if ((*arg != '_') && (!ft_isalnum(*arg)))
			return (0);
		arg ++;
	}
	return (1);
}

char	**findinenv(char *arg, char **env)
{
	char	*var;
	int		varsize;
	char	*equalptr;

	if (!arg || !env)
		return (0);
	equalptr = ft_strchr(arg, '=');
	if (equalptr)
		var = getstr(arg, equalptr);
	else
		var = ft_strdup(arg);
	varsize = ft_strlen(var);
	while (*env)
	{
		if (!ft_strncmp(*env, var, varsize) && \
(*(*env + varsize) == '=' || *(*env + varsize) == 0))
		{
			free(var);
			return (env);
		}
		env++;
	}
	free(var);
	return (0);
}

void	replaceinenv(char *arg, char **foundenv)
{
	char	*temp;

	if (!foundenv || !arg)
		return ;
	temp = *foundenv;
	*foundenv = ft_strdup(arg);
	free(temp);
}

void	freeenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
