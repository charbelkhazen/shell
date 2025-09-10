/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   applyexp_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:59:34 by jissa             #+#    #+#             */
/*   Updated: 2025/09/10 20:48:50 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_modifiable	*expandbuff(char *cmd, int status, char ***envp)
{
	char			*exp;
	t_modifiable	*mod;

	exp = ft_strchr(cmd, '$');
	if (!exp)
		return (0);
	mod = con_modifiable(cmd, exp);
	while (mod -> exp)
	{
		mod = modify(mod, status, envp);
		mod -> exp = ft_strchr((mod -> start) + (mod -> steps), '$');
		if (mod -> exp)
		{
			if (*((mod -> exp) + 1) == '?')
				(mod -> endexp) = (mod -> exp) + 2;
			else if (ft_isdigit(*((mod -> exp) + 1)))
				(mod -> endexp) = (mod -> exp) + 2;
			else
				mod -> endexp = tononalnum((mod -> exp) + 1);
		}
	}
	return (mod);
}

void	freemod(t_modifiable *mod)
{
	if (mod -> start)
		free(mod -> start);
	free(mod);
}

char	*applyexp(char *cmd, int type, int status, char ***envp)
{
	t_modifiable	*mod;

	if (type == '\'')
		return (cmd);
	mod = expandbuff(cmd, status, envp);
	if (!mod)
		return (cmd);
	cmd = ft_strdup(mod -> start);
	freemod(mod);
	return (cmd);
}
