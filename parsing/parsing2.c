/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:03:40 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 18:08:17 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*parseredir(char **buf, t_tree *tree, int status)
{
	int		redir;
	char	*startfn;
	char	*endfn;
	char	*filename;
	t_tree	**tail;

	tail = &tree;
	while ((*tail)->type == '<' || (*tail)->type == '>' \
|| (*tail)->type == 'h' || (*tail)->type == 'a')
		tail = &((t_redirtree *)*tail)->cmd;
	while (match(*buf, "><"))
	{
		redir = consume(buf, NULL, NULL);
		if (consume(buf, &startfn, &endfn) != 'w')
		{
			printf("Syntax error near unexpected token '%c'\n", redir);
			freetree(tree);
			return (NULL);
		}
		filename = getstr(startfn, endfn);
		*tail = con_redirtree(*tail, redir, filename);
		tail = &((t_redirtree *)*tail)-> cmd;
	}
	return (tree);
}

void	freepipe(t_tree *tree, t_pipetree *pipetree)
{
	pipetree = (t_pipetree *)tree;
	freetree(pipetree -> right);
	freetree(pipetree -> left);
	free(pipetree);
}

void	freeredir(t_tree *tree, t_redirtree *redirtree)
{
	redirtree = (t_redirtree *)tree;
	freetree(redirtree -> cmd);
	free(redirtree -> file_name);
	free(redirtree);
}

void	freetree(t_tree *tree)
{
	t_pipetree	*pipetree;
	t_redirtree	*redirtree;
	t_cmdtree	*cmdtree;
	char		**argv;

	if (tree -> type == 'w')
	{
		cmdtree = (t_cmdtree *)tree;
		argv = cmdtree -> cmd;
		while (*argv)
		{
			free(*argv);
			argv ++;
		}
		free(cmdtree);
	}
	else if (tree -> type == '|')
		freepipe(tree, pipetree);
	else if ((tree -> type == '>') || (tree -> type == '<') || \
(tree -> type == 'a') || (tree -> type == 'h'))
		freeredir(tree, redirtree);
}
