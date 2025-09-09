/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:24:37 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 16:03:51 by chkhazen         ###   ########.fr       */
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

int     export_builtin(char **args, char ***env) //Use handleword() to handle expansions and quotations  {
        int     status;
        char    *var;

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
