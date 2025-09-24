/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:43:40 by jissa             #+#    #+#             */
/*   Updated: 2025/09/24 11:16:07 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ishdinleft(t_tree *tree)
{
	while (tree ->type == '<' || tree -> type == '>' \
		 || tree ->type == 'h' || tree ->type == 'a')
	{
		if (tree -> type == 'h')
			return (1);
		tree = ((t_redirtree *)tree) -> cmd;
	}
	return (0);
}

void	exec_pipe(t_pipetree *tree, char ***envp, int *status)
{
	int		pipefd[2];
	int		heredocflag;
	pid_t	pid1;
	pid_t	pid2;

	heredocflag = ishdinleft(tree -> left);
	pipe(pipefd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		trav_tree(tree->left, envp, status);
	}
	if (heredocflag)
		waitpid(pid1, status, 0);
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
		trav_tree(tree->right, envp, status);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, status, 0);
	waitpid(pid2, status, 0);
}
