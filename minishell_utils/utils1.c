/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:10:07 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 18:11:14 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_iswhitespace(char *s)
{
	if (*s == 32 || (*s >= 9 && *s <= 13))
		return (1);
	else
		return (0);
}

int	chariswhitespace(char s)
{
	return (s == 32 || (s >= 9 && s <= 13));
}

int	isexit(char *s)
{
	if (ft_strchr(s, '|'))
		return (0);
	s = skipwhitespace(s);
	if (!ft_strncmp(s, "exit", 4) && (ft_iswhitespace(s + 4) || *(s + 4) == 0))
		return (1);
	return (0);
}
