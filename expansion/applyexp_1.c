/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   applyexp_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:58:54 by jissa             #+#    #+#             */
/*   Updated: 2025/09/04 10:01:16 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
