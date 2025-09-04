/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleword2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:34:33 by jissa             #+#    #+#             */
/*   Updated: 2025/09/04 11:35:01 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	utiltravword1(int token, char **cur, char **start, char **end)
{
	token = '"';
	(*cur)++;
	*start = *cur;
	while ((**cur) != '"' && (**cur))
		(*cur)++;
	*end = *cur;
	(*cur)++;
	return (token);
}

int	utiltravword2(int token, char **cur, char **start, char **end)
{
	token = '\'';
	(*cur)++;
	*start = *cur;
	while ((**cur) != '\'' && (**cur))
		(*cur)++;
	*end = *cur;
	(*cur)++;
	return (token);
}

int	travword(char **cur, char **start, char **end)
{
	int	token;

	if (**cur == 0)
		token = 0;
	else if ((**cur) == '"')
		return (utiltravword1(token, cur, start, end));
	else if ((**cur) == '\'')
		return (utiltravword2(token, cur, start, end));
	else
	{
		*start = *cur;
		token = 'w';
		while (**cur && (!ft_strchr("' \"", **cur)))
			(*cur)++;
		*end = *cur;
	}
	return (token);
}

char	*expand_slice(char *start, char *end, int tok, int status)
{
	char	*tmp;
	char	*res;

	tmp = getstr(start, end);
	if (!tmp)
		return (ft_strdup(""));
	res = applyexp(tmp, tok, status);
	return (res);
}
