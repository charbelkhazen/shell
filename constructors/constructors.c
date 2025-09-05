/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:02:32 by jissa             #+#    #+#             */
/*   Updated: 2025/09/05 13:52:51 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*con_cmdtree(void)
{
	t_cmdtree	*tree;

	tree = malloc(sizeof(t_cmdtree));
	tree -> type = 'w';
	*(tree -> cmd) = 0;
	return ((t_tree *)tree);
}

t_tree	*con_pipetree(t_tree *left, t_tree *right)
{
	t_pipetree	*tree;

	tree = malloc(sizeof(t_pipetree));
	tree -> type = '|';
	tree -> left = left;
	tree -> right = right;
	return ((t_tree *)tree);
}

void	setoption_fd(t_redirtree *tree, int option, int fd)
{
	tree -> option = option;
	tree -> fd = fd;
}

t_tree	*con_redirtree(t_tree *cmd, int type, char *fn)
{
	t_redirtree	*tree;

	tree = malloc(sizeof(t_redirtree));
	tree -> type = type;
	if (type == '>')
		setoption_fd(tree, O_WRONLY | O_TRUNC | O_CREAT, 1);
	else if (type == '<')
		setoption_fd(tree, O_RDONLY, 0);
	else if (type == 'a')
		setoption_fd(tree, O_WRONLY | O_CREAT | O_APPEND, 1);
	else if (type == 'h')
		setoption_fd(tree, -1, 0);
	tree -> cmd = cmd;
	tree -> file_name = fn;
	return ((t_tree *)tree);
}
