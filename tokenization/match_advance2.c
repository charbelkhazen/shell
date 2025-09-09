/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_advance2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:57:13 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 17:59:25 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	consumeoutredirs(int *token, char **curr)
{
	(*curr)++;
	if ((**curr) == '>')
	{
		*token = 'a';
		(*curr)++;
	}
	else
		*token = '>';
}

void	consumeinredirs(int *token, char **curr)
{
	(*curr)++;
	if ((**curr) == '<')
	{
		*token = 'h';
		(*curr)++;
	}
	else
		*token = '<';
}

void	consumeword(int *token, char **curr)
{
	*token = 'w';
	while (**curr && !ft_strchr("|&< >", **curr))
	{
		if (**curr == '\'')
		{
			(*curr)++;
			while (**curr != '\'' && **curr)
				(*curr)++;
		}
		if (**curr == '"')
		{
			(*curr)++;
			while (**curr != '"' && **curr)
				(*curr)++;
		}
		if (!**curr)
			break ;
		(*curr)++;
	}
}

int	consume(char **curr, char **tok, char **endtok)
{
	int	token;

	*curr = skipwhitespace(*curr);
	if (tok)
		*tok = *curr;
	if (**curr == 0)
		token = 0;
	else if ((**curr) == '|')
		consumepipe(&token, curr);
	else if ((**curr) == '>')
		consumeoutredirs(&token, curr);
	else if ((**curr) == '<')
		consumeinredirs(&token, curr);
	else
		consumeword(&token, curr);
	if (endtok)
		*endtok = *curr;
	*curr = skipwhitespace(*curr);
	return (token);
}

char	*getstr(char *start, char *end)
{
	int		len;
	int		i;
	char	*str;

	len = end - start;
	if (len == 0)
		return (0);
	str = malloc(len + 1);
	i = 0;
	while (i < len)
	{
		str[i] = *(start + i);
		i++;
	}
	str[i] = 0;
	return (str);
}
