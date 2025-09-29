/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:13:26 by jissa             #+#    #+#             */
/*   Updated: 2025/09/29 12:43:51 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	applybuiltin(char *input, char ***envp, int oldstatus)
{
	char	**args;
	int		status;

	status = 0;
	args = get_args(input, oldstatus, envp); 
	if (isexit(input))
		status = (exit_builtin(args, *envp, 1, oldstatus));
	else if (iscd(input))
		status = (change_directory(args, envp));
	else if (isexport(input))
		status = (export_builtin(args, envp));
	else if (isunset(input))
		status = (unset_builtin(args, envp));
	free_args(args);
	return (status);
}

char	isquote(char *str)
{
	char	*s;

	s = str;
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
	s = str;
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

void	writeexpinput(char *buf, int *pipefd, char ***env)
{
	char	*sword;
	char	*eword;
	char	*word;
	char	*transword;

	while (*buf)
	{
		if (chariswhitespace(*buf) && *buf)
			write(pipefd[1], buf ++, 1);
		else
		{
			sword = buf;
			while (!chariswhitespace(*buf) && *buf)
				buf++;
			eword = buf;
			word = getstr(sword, eword);
			transword = handleword(word, 0, env);
			write(pipefd[1], transword, ft_strlen(transword));
			free(word);
			free(transword);
		}
	}
}

// char	*removequotes(char *str)
// {
// 	char	*s;

// 	s = str;
// 	while (*s && *(s + 1))
// 	{
// 		if (*s == '"')
// 		{
// 			s++;
// 			if (*s == '"')
// 				return (ft_strdup(""));
// 			while (*s && (*s != '"'))
// 				s++;
// 			if (*s == '"')
// 				return (getstr(str + 1, s));
// 		}
// 		s++;
// 	}
// 	// else if (*s == '\'')
// 	// {
// 	// 	s++;
// 	// 	if (*s == '\'')
// 	// 		return (ft_strdup(""));
// 	// 	while (*s && (*s != '\''))
// 	// 		s++;
// 	// 	if (*s == '\'')
// 	// 		return (getstr(str + 1, s));
// 	// }
// 	return (0);
// }

char	*removequotes(char *str, int *flag)
{
	int		i;
	int		j;
	char	*unquoted_str;

	unquoted_str = malloc(ft_strlen(str) + 1);
	if (!unquoted_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			unquoted_str[j] = str[i];
			j++;
		}
		i++;
	}
	unquoted_str[j] = 0;
	*flag = 1;
	return (unquoted_str);
}

void	freeshlvl(char **my_env)
{
	int	i;

	i = 0;
	while (my_env[i])
	{
		if (ft_strncmp(my_env[i], "SHLVL=", 6) == 0)
			free(my_env[i]);
		i++;
	}
}
