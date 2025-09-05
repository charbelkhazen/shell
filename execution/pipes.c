/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:43:40 by jissa             #+#    #+#             */
/*   Updated: 2025/09/05 19:10:31 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipe(t_pipetree *tree, char **envp, int *status, char *freevar)
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
		trav_tree(tree->left, envp, status, freevar);
	}
	waitpid(pid1, status, 0);
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
		trav_tree(tree->right, envp, status, freevar);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid2, status, 0);
}
