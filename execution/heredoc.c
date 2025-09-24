/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:41:34 by jissa             #+#    #+#             */
/*   Updated: 2025/09/24 12:23:07 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	utilprocessinput(char *delim)
{
	char	isexpand;

	if (isquote(delim))
		isexpand = 0;
	else
		isexpand = 1;
	return (isexpand);
}

void	processinput(char *delim, int *pipefd, char ***env)
{
	char	*input;
	char	isexpand;
	char	*cmpdelim;

	isexpand = utilprocessinput(delim);
	input = readline("heredoc> ");
	if (removequotes(delim))
		cmpdelim = removequotes(delim);
	else
		cmpdelim = delim;
	while (input && (!(*input) || (ft_strcmp(input, cmpdelim) != 0)))
	{
		if (isexpand)
			writeexpinput(input, pipefd, env);
		else
			write(pipefd[1], input, ft_strlen(input));
		write(pipefd[1], "\n", 1);
		free(input);
		input = readline("heredoc> ");
	}
	if (removequotes(delim))
		free(cmpdelim);
	free(input);
}

void	writepipe(char *delim, int *pipefd, char ***env)
{
	int	temppidout;
	int	temppidin;
	int	ttyfd;

	temppidout = dup(STDOUT_FILENO);
	temppidin = dup(STDIN_FILENO);
	ttyfd = open("/dev/tty", O_RDWR);
	dup2(ttyfd, STDOUT_FILENO);
	dup2(ttyfd, STDIN_FILENO);
	processinput(delim, pipefd, env);
	close(ttyfd);
	dup2(temppidin, STDIN_FILENO);
	dup2(temppidout, STDOUT_FILENO);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	exec_heredoc(t_redirtree *tree, char ***env, int *status)
{
	char	*delim;
	int		pipefd[2];

	delim = tree->file_name;
	pipe(pipefd);
	writepipe(delim, pipefd, env);
	trav_tree(tree->cmd, env, status);
	exit(127);
}
