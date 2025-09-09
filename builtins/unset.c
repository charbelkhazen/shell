/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:24:37 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 18:31:10 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
int	unset_builtin(char **args, char **env)
{
	int	i;
	int	j;

	if (!args[1])
		return (0);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], args[1], strlen(args[1])) == 0 \
&& env[i][strlen(args[1])] == '=')
		{
			j = i;
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			continue ;
		}
		i++;
	}
	return (0);
}
*/

void	removeenvvar(char *arg, char ***env, char **foundenv)
{
	int	i;
	char	**orig;
	int	index;
	int	j;

	index = (int) (foundenv - *env);
	//printf("DIFF:%d\n", index);
	i = 0;
	while (*(*env + i))
                i++;
        orig = *env;
        *env = malloc(sizeof(char *) * i);
        i = 0;
	while (i < index)
	{
		//printf("i: %d\n", i);
                *(*env + i) = ft_strdup(*(orig + i));
		i ++;
	}
	j = i;
	if (*(orig + i))
	{
		//printf("i: %d\n", i);
		i ++;
	}
        while (*(orig + i))
        {
		//printf("i: %d, j: %d\n", i, j);
                *(*env + j) = ft_strdup(*(orig + i));
                i++;
		j++;
        }
        *(*env + j) = 0;
        freeenv(orig);
}

void    applyunset(char *arg, char ***env)
{
        char    **foundenv;

        foundenv = findinenv(arg, *env);
	if (foundenv)
		removeenvvar(arg, env, foundenv);
}

int     unset_builtin(char **args, char ***env)
{
        char    *var;

        if (!args[1])
                return (0);
        args++;
        while (*args)
	{
		applyunset(*args, env);
		args++;
	}
	/*
	while (**env)
	{
		printf(">%s\n", **env);
		(*env)++;
	}
	*/
	return (0);
}
