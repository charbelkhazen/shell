/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:25:58 by chkhazen          #+#    #+#             */
/*   Updated: 2025/09/28 18:01:56 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	addinenv(char *arg, char ***env)
{
	int		i;
	char	**temp;

	i = 0;
	while (*(*env + i))
		i++;
	temp = *env;
	*env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (*(temp + i))
	{
		*(*env + i) = ft_strdup(*(temp + i));
		i++;
	}
	*(*env + i) = ft_strdup(arg);
	i++;
	*(*env + i) = 0;
	freeenv(temp);
}

void	applyexport(char *arg, char ***env)
{
	char	**foundenv;

	foundenv = findinenv(arg, *env);
	if (ft_strchr(arg, '='))
	{
		if (foundenv)
			replaceinenv(arg, foundenv);
		else
			addinenv(arg, env);
	}
	else
	{
		if (foundenv)
			return ;
		else
			addinenv(arg, env);
	}
}

int	export_builtin(char **args, char ***env)
{
	int		status;

	status = 0;
	if (!args[1])
	{
		handle_exportcmd(*env);
		return (0);
	}
	args++;
	while (*args)
	{
		if (!validatearg(*args))
		{
			printf("Minishell: export: '%s': not a valid identifier\n", *args);
			status = 1;
		}
		else
			applyexport(*args, env);
		args ++;
	}
	return (status);
}
/*
int main(int ac, char *av[], char *envp[])
{
	char **env = dupenv(envp);
	myexport(av, &env);
	int i=0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	freeenv(env);
}
*/
