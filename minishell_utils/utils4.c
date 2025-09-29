/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkhazen <chkhazen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:37:33 by jissa             #+#    #+#             */
/*   Updated: 2025/09/29 12:54:07 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**defaultfill(void)
{
	char	**dup;
	char	cwd[256];

	dup = malloc(sizeof(char *) * 4);
	getcwd(cwd, sizeof(cwd));
	dup[0] = ft_strjoin("PWD=", cwd);
	dup[1] = ft_strdup("SHLVL=0");
	dup[2] = ft_strdup("_=/usr/bin/env");
	dup[3] = 0;
	return (dup);
}

char	**dupenv(char **envp)
{
	int		i;
	char	**dup;

	if (!(envp) || !(*envp) || !(**envp))
		return (defaultfill());
	i = 0;
	while (envp[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		dup[i] = ft_strdup(envp[i]);
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	*ft_getenv(char *var, char **env)
{
	int		i;
	int		sizevar;
	char	*val;

	if (!var || !(*var) || !env)
		return (0);
	sizevar = (int)ft_strlen(var);
	i = 0;
	val = 0;
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], sizevar) && ((*(env[i] + sizevar) == '=') \
|| (*(env[i] + sizevar) == 0)))
		{
			if (ft_strchr(env[i], '='))
				val = (ft_strchr(env[i], '=') + 1);
			if (val)
				return (val);
		}
		i++;
	}
	return (0);
}

void	util_get_args(char *input, char **args, int status, char ***env)
{
	char	*sarg;
	char	*earg;
	char	*word;
	int		i;
	char	*tempword;

	i = 0;
	while (consume(&input, &sarg, &earg))
	{
		tempword = getstr(sarg, earg);
		word = handleword(tempword, status, env);
		printf(">%s\n", word);
		args[i] = word;
		if (tempword)
			free(tempword);
		if (word && !(*word))
		{
			free(word);
			word = 0;
		}
		i ++;
		printf("1\n");
	}
}

char	**get_args(char *input, int status, char ***env)
{
	char	**args;

	if (!input)
		return (0);
	args = ft_calloc(sizeof(char *) * 100, 1);
	util_get_args(input, args, status, env);
	return (args);
}
