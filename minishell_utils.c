/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:21:17 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 16:29:26 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_iswhitespace(char *s)
{
	if (*s == 32 || (*s >= 9 && *s <= 13))
		return (1);
	else
		return (0);
}

int	chariswhitespace(char s)
{
	return (s == 32 || (s >= 9 && s <= 13));
}

int	isexit(char *s)
{
	if (ft_strchr(s, '|'))
		return (0);
	s = skipwhitespace(s);
	if (!ft_strncmp(s, "exit", 4) && (ft_iswhitespace(s + 4) || *(s+4) == 0))
		return (1);
	return (0);
}

int	iscd(char *s)
{
	if (ft_strchr(s, '|'))
		return (0);
	s = skipwhitespace(s);
	if (!ft_strncmp(s, "cd", 2) && (ft_iswhitespace(s + 2) || *(s+2) == 0))
		return (1);
	return (0);
}

int	isexport(char *s)
{
	if (ft_strchr(s, '|'))
		return (0);
	s = skipwhitespace(s);
	if (!ft_strncmp(s, "export", 6) && (ft_iswhitespace(s + 6) || *(s + 6) == 0))
		return (1);
	return (0);
}

int	isunset(char *s)
{
	if (ft_strchr(s, '|'))
		return (0);
	s = skipwhitespace(s);
	if (!ft_strncmp(s, "unset",5) && (ft_iswhitespace(s + 5) || *(s+ 5) == 0))
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

void    free_args(char **args)
{
	int i = 0;

	if (!args)
		return;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
int	applybuiltin(char *input, char ***envp)
{
	char	**args;
	int	status;

	args = ft_split(input, ' '); //TO BE FREEEDDDDD
	if (isexit(input)) 
		status= (exit_builtin(args, *envp));
	else if (iscd(input))
		status= (change_directory(args, *envp));
	else if (isexport(input))
		status= (export_builtin(args, envp));
	else if (isunset(input))
		status= (unset_builtin(args, envp));
	free_args(args);
	return (status);
}

char	isquote(char *str)
{
	char	*s;

	s = str;
	if (*s == '"')
	{
		s ++;
		while(*s && *(s + 1))
			s ++;
		if (*s == '"')
			return (1);
	}
	if (*s == '\'')
	{
		s ++;
		while(*(s + 1) != 0)
			s ++;
		if (*s == '\'')
			return (1);
	}
	return (0);
}
void    writeexpinput(char *buf, int *pipefd)
{
        int     tok;
        char    *sword;
        char    *eword;
        char    *word;
        char    *transword;

        while (*buf)
        {
                if (chariswhitespace(*buf) && *buf)
                        write(pipefd[1], buf ++, 1);
                else
                {
                        sword = buf;
                        while(!chariswhitespace(*buf) && *buf)
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
		s ++;
		if (*s == '"')
			return (ft_strdup(""));
		while (*s && (*s != '"'))
			s ++; 
		if (*s == '"')
			return (getstr(str + 1, s));
	}
	else if (*s == '\'')
	{
		s ++;
		if (*s == '\'')
			return (ft_strdup(""));
		while (*s && (*s != '\''))
			s ++; 
		if (*s == '\'')
			return (getstr(str + 1, s));
	}
	return (0);
}

void    freeshlvl(char **my_env)
{
        int             i = 0;

        while (my_env[i])
        {
                if (ft_strncmp(my_env[i], "SHLVL=", 6) == 0)
                        free(my_env[i]);
                i++;
        }
}

char    **dupenv(char **envp) 
{
        int     i;
        char    **dup;

        i = 0;
        while (envp[i])
                i ++;
        dup = malloc(sizeof(char *) * (i + 1));
        i = 0;
        while(envp[i])
        {
                dup[i] = ft_strdup(envp[i]);
                i ++;
        }
        dup[i] = 0;
        return (dup);
}
