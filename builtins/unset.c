/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:24:37 by jissa             #+#    #+#             */
/*   Updated: 2025/09/10 19:01:07 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	utilremoveenvvar(int *i, char ***env, char ***orig)
{
	*i = 0;
	while (*(*env + (*i)))
		(*i)++;
	*orig = *env;
}

void	removeenvvar(char *arg, char ***env, char **foundenv)
{
	int		i;
	char	**orig;
	int		index;
	int		j;

	(void) arg;
	index = (int)(foundenv - *env);
	utilremoveenvvar(&i, env, &orig);
	*env = malloc(sizeof(char *) * i);
	i = 0;
	while (i < index)
	{
		*(*env + i) = ft_strdup(*(orig + i));
		i ++;
	}
	j = i;
	if (*(orig + i))
		i ++;
	while (*(orig + i))
	{
		*(*env + j) = ft_strdup(*(orig + i));
		i++;
		j++;
	}
	*(*env + j) = 0;
	freeenv(orig);
}

void	applyunset(char *arg, char ***env)
{
	char	**foundenv;

	foundenv = findinenv(arg, *env);
	if (foundenv)
		removeenvvar(arg, env, foundenv);
}

int	unset_builtin(char **args, char ***env)
{
	if (!args[1])
		return (0);
	args++;
	while (*args)
	{
		applyunset(*args, env);
		args++;
	}
	return (0);
}
