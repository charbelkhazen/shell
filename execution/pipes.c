/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:43:40 by jissa             #+#    #+#             */
/*   Updated: 2025/09/16 14:29:21 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipe(t_pipetree *tree, char ***envp, int *status)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(pipefd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		trav_tree(tree->left, envp, status);
	}
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
