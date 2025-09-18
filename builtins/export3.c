/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:21:16 by jissa             #+#    #+#             */
/*   Updated: 2025/09/18 15:58:59 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_envp(char **envp)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char	*quoted_value(char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin("\"", value);
	res = ft_strjoin(tmp, "\"");
	free(tmp);
	return (res);
}

void	add_quotes(char **envp)
{
	int		i;
	char	*value;
	char	*new_entry;
	char	*final_value;
	char	*extracted_var;

	i = 0;
	while (envp[i])
	{
		value = ft_strchr(envp[i], '=');
		if (value)
		{
			extracted_var = ft_substr(envp[i], 0, \
(ft_strlen(envp[i]) - ft_strlen(value)) + 1);
			final_value = quoted_value(value + 1);
			new_entry = ft_strjoin(extracted_var, final_value);
			free(extracted_var);
			free(final_value);
			free(envp[i]);
			envp[i] = new_entry;
		}
		i++;
	}
}
