/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:37:33 by jissa             #+#    #+#             */
/*   Updated: 2025/09/11 11:06:47 by chkhazen         ###   ########.fr       */
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

	if (!var || !(*var) || !env)
		return (0);
	sizevar = (int)ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], sizevar) && ((*(env[i] + sizevar) == '=') || (*(env[i] + sizevar) == 0))) 
			return (ft_strchr(env[i], '=') + 1);
		i ++;
	}
	return (0);
}
