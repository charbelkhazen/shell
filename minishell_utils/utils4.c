/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:37:33 by jissa             #+#    #+#             */
/*   Updated: 2025/09/11 12:07:28 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**dupenv(char **envp)
{
	int		i;
	char	**dup;

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
	int	i;
	int	sizevar;
	char	*val;

	if (!var || !(*var) || !env)
		return (0);
	sizevar = (int)ft_strlen(var);
	i = 0;
	val = 0;
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], sizevar) && ((*(env[i] + sizevar) == '=') || (*(env[i] + sizevar) == 0))) 
		{
			if(ft_strchr(env[i], '='))
				val = (ft_strchr(env[i], '=') + 1);
			if (val)
				return (val);
		}
		i ++;
	}
	return (0);
}
