/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trav_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:45:38 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 12:01:15 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trav_tree(t_tree *tree, char ***envp, int *status)
{
	if (!tree)
		return ;
	if (tree->type == 'w')
		exec_command_node((t_cmdtree *)tree, envp, status);
	else if (tree->type == '|')
		exec_pipe((t_pipetree *)tree, envp, status);
	else if (tree->type == '<' || tree->type == '>' || tree->type == 'a')
		exec_input_redir((t_redirtree *)tree, envp, status);
	else if (tree->type == 'h')
		exec_heredoc((t_redirtree *)tree, envp, status);
	exit(WEXITSTATUS(*status));
}
