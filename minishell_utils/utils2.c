/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:11:23 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 18:13:15 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	iscd(char *s)
{
	if (ft_strchr(s, '|'))
		return (0);
	s = skipwhitespace(s);
	if (!ft_strncmp(s, "cd", 2) && (ft_iswhitespace(s + 2) || *(s + 2) == 0))
		return (1);
	return (0);
}

int	isexport(char *s)
{
	if (ft_strchr(s, '|'))
		return (0);
	s = skipwhitespace(s);
	if (!ft_strncmp(s, "export", 6) && (ft_iswhitespace(s + 6) || \
*(s + 6) == 0))
		return (1);
	return (0);
}

int	isunset(char *s)
{
	if (ft_strchr(s, '|'))
		return (0);
	s = skipwhitespace(s);
	if (!ft_strncmp(s, "unset", 5) && (ft_iswhitespace(s + 5) || *(s + 5) == 0))
		return (1);
	return (0);
}

int	startbuiltin(char *s)
{
	if (isunset(s) || isexport(s) || iscd(s) || isexit(s))
		return (1);
	else
		return (0);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
