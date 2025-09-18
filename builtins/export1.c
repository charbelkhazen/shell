/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:44:55 by chkhazen          #+#    #+#             */
/*   Updated: 2025/09/18 15:59:35 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_exportcmd(char **envp)
{
	int		i;
	char	**env_cpy;

	env_cpy = dupenv(envp);
	i = 0;
	sort_envp(env_cpy);
	add_quotes(env_cpy);
	while (env_cpy[i])
	{
		printf("declare -x %s\n", env_cpy[i]);
		i++;
	}
	freeenv(env_cpy);
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
