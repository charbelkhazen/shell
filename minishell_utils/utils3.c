/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:13:26 by jissa             #+#    #+#             */
/*   Updated: 2025/09/10 18:14:43 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	applybuiltin(char *input, char ***envp, int oldstatus)
{
	char	**args;
	int		status;
	int		i;
	char	*temp;

	args = ft_split(input, ' ');
	i = 0;
	while (args[i])
	{
		temp = args[i];
		args[i] = handleword(args[i], WEXITSTATUS(oldstatus));
		free(temp);
		i++;
	}
	if (isexit(input))
		status = (exit_builtin(args, *envp));
	else if (iscd(input))
		status = (change_directory(args, *envp));
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
	if (*s == '"')
	{
		s++;
		while (*s && *(s + 1))
			s++;
		if (*s == '"')
			return (1);
	}
	if (*s == '\'')
	{
		s++;
		while (*(s + 1) != 0)
			s++;
		if (*s == '\'')
			return (1);
	}
	return (0);
}

void	writeexpinput(char *buf, int *pipefd)
{
	int		tok;
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
			transword = handleword(word, 0);
			write(pipefd[1], transword, ft_strlen(transword));
			free(word);
			free(transword);
		}
	}
}

char	*removequotes(char *str)
{
	char	*s;

	s = str;
	if (*s == '"')
	{
		s++;
		if (*s == '"')
			return (ft_strdup(""));
		while (*s && (*s != '"'))
			s++;
		if (*s == '"')
			return (getstr(str + 1, s));
	}
	else if (*s == '\'')
	{
		s++;
		if (*s == '\'')
			return (ft_strdup(""));
		while (*s && (*s != '\''))
			s++;
		if (*s == '\'')
			return (getstr(str + 1, s));
	}
	return (0);
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
