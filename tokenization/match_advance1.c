/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_advance1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:55:39 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 17:56:50 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*skipwhitespace(char *ptr)
{
	while ((*ptr >= 9 && *ptr <= 13) || (*ptr == 32))
		(ptr)++;
	return (ptr);
}

char	*towhitespace(char *ptr)
{
	while (*ptr && !(*ptr == 32 || (*ptr >= 9 && *ptr <= 13)))
		(ptr)++;
	return (ptr);
}

char	*tononalnum(char *ptr)
{
	while (*ptr && ft_isalnum(*ptr))
		(ptr)++;
	return (ptr);
}

int	match(char *ptr, char *tok)
{
	ptr = skipwhitespace(ptr);
	return (*ptr && ft_strchr(tok, *ptr));
}

void	consumepipe(int *token, char **curr)
{
	*token = '|';
	(*curr)++;
}
