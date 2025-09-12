/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:37:33 by jissa             #+#    #+#             */
/*   Updated: 2025/09/12 15:41:42 by jissa            ###   ########.fr       */
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
