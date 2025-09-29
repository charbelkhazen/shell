/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:03:31 by jissa             #+#    #+#             */
/*   Updated: 2025/09/29 13:03:55 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isdoublequote(char *s)
{
	while (*s && *(s + 1))
	{
		if (*s == '"')
		{
			while (*s && *s != '"')
				s++;
			if (*s == '"')
				return (1);
		}
		s++;
	}
	return (0);
}

int	issinglequote(char *s)
{
	while (*s && *(s + 1))
	{
		if (*s == '\'')
		{
			while (*s && *s != '\'')
				s++;
			if (*s == '\'')
				return (1);
		}
		s++;
	}
	return (0);
}

char	isquote(char *str)
{
	char	*s;

	s = str;
	if (isdoublequote(s))
		return (1);
	s = str;
	if (issinglequote(s))
		return (1);
	return (0);
}
