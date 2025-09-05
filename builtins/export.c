/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:35:16 by jissa             #+#    #+#             */
/*   Updated: 2025/09/05 19:35:36 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_exportcmd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

char	*create_new_env_var(char *arg, char **var_name)
{
	char	*var_value;
	char	*new_env_var;

    if (!ft_strchr(arg, '='))
    {
        *var_name = ft_strdup(arg);
        new_env_var = ft_strdup(arg);
    }
	else
	{
		var_value = ft_strchr(arg, '=');
		*var_name = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(var_value));
		new_env_var = ft_strjoin(*var_name, var_value);
	}
	return (new_env_var);
}

int	update_existing_env(char **envp, char *var_name, char *new_env_var, int has_equal)
{
	int	i;
	int	len;

	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(var_name, envp[i], len) == 0
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
		{
			if (has_equal)
				envp[i] = ft_strdup(new_env_var);
			return (1);
		}
		i++;
	}
	return (0);
}

void	add_new_env_var(char **envp, char *new_env_var)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = ft_strdup(new_env_var);
	envp[i + 1] = NULL;
}

int	export_builtin(char **args, char **envp, char *freevar)
{
	char	*var_name;
	char	*new_env_var;
	char	*equal_sign;
	int		found;
	int		has_equal;

	//printf("%s\n", freevar);
	if (!args[1])
	{
		handle_exportcmd(envp);
		return (0);
	}
	equal_sign = ft_strchr(args[1], '=');
	has_equal = (equal_sign != NULL);
	new_env_var = create_new_env_var(args[1], &var_name);
	found = update_existing_env(envp, var_name, new_env_var, has_equal);
	if (!found)
		add_new_env_var(envp, new_env_var);
	//printf("%s\n", var_name);
	free(var_name);
	free(new_env_var);
	return (0);
}


// ==582719== 11 bytes in 1 blocks are still reachable in loss record 3 of 68
// ==582719==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==582719==    by 0x10DA5B: ft_strdup (in /home/jissa/42core/minishell/a.out)
// ==582719==    by 0x10A306: update_existing_env (in /home/jissa/42core/minishell/a.out)
// ==582719==    by 0x10A46F: export_builtin (in /home/jissa/42core/minishell/a.out)
// ==582719==    by 0x10CE3A: applybuiltin (in /home/jissa/42core/minishell/a.out)
// ==582719==    by 0x10AB3D: handlestartbuiltin (in /home/jissa/42core/minishell/a.out)
// ==582719==    by 0x10ACDA: main (in /home/jissa/42core/minishell/a.out)

