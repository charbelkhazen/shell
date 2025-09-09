/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:42:21 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 11:59:25 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_input_redir(t_redirtree *tree, char ***env, int *status)
{
	int	fd;

	if (tree->fd == 0)
		fd = open(tree->file_name, tree->option);
	else if (tree->fd == 1)
		fd = open(tree->file_name, tree->option, 0644);
	else
		return ;
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, tree->fd);
	close(fd);
	trav_tree(tree->cmd, env, status);
}
