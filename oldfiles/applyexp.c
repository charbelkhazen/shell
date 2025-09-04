/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   applyexp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:56:03 by jissa             #+#    #+#             */
/*   Updated: 2025/09/04 09:58:13 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_modifiable	*con_modifiable(char *cmd, char *exp)
{
	t_modifiable	*mod;

	mod = malloc(sizeof(t_modifiable));
	if (!mod)
		return (NULL);
	mod -> start = cmd;
	mod -> exp = exp;
	if (*((mod -> exp) + 1) == '?')
		(mod -> endexp) = (mod -> exp) + 2;
	else if (ft_isdigit(*((mod -> exp) + 1)))
		(mod -> endexp) = (mod -> exp) + 2;
	else
		mod -> endexp = tononalnum(exp + 1);
	return (mod);
}

void	mergeremain(char *merge, t_modifiable *mod)
{
	char	*temp;

	if (*(mod -> endexp))
	{
		temp = merge;
		merge = ft_strjoin(merge, mod -> endexp);
		free(temp);
	}
	temp = mod -> start;
	mod -> start = merge;
	free(temp);
}

char	*utilmodify(char *exp, char *rep, int status)
{
	if (!exp)
		rep = "$";
	else if (*exp == '?')
		rep = ft_itoa(status);
	else if (ft_isdigit(*exp))
		rep = "";
	else
		rep = getenv(exp);
	return (rep);
}

t_modifiable	*modify(t_modifiable *mod, int status)
{
	char	*pre;
	char	*exp;
	char	*rep;
	char	*merge;

	pre = getstr(mod -> start, mod -> exp);
	if (!pre)
		pre = "";
	exp = getstr((mod -> exp) + 1, mod -> endexp);
	rep = utilmodify(exp, rep, status);
	if (!rep)
		rep = "";
	merge = ft_strjoin(pre, rep);
	if (pre && *pre)
		free(pre);
	if (exp && *exp == '?')
		free(rep);
	if (exp)
		free(exp);
	mod -> steps = ft_strlen(merge);
	mergeremain(merge, mod);
	return (mod);
}

t_modifiable	*expandbuff(char *cmd, int status)
{
	char			*exp;
	t_modifiable	*mod;

	exp = ft_strchr(cmd, '$');
	if (!exp)
		return (0);
	mod = con_modifiable(cmd, exp);
	while (mod -> exp)
	{
		mod = modify(mod, status);
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

char	*applyexp(char *cmd, int type, int status)
{
	t_modifiable	*mod;

	if (type == '\'')
		return (cmd);
	mod = expandbuff(cmd, status);
	if (!mod)
		return (cmd);
	cmd = ft_strdup(mod -> start);
	freemod(mod);
	return (cmd);
}
