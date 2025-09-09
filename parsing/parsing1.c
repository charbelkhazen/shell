/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:59:46 by jissa             #+#    #+#             */
/*   Updated: 2025/09/09 18:03:26 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*parseprogram(char **buf, int status)
{
	t_tree	*tree;

	if (globsig == SIGINT)
	{
		globsig = 0;
		status = 128 + SIGINT;
	}
	else if (!(WIFEXITED(status)) && (WTERMSIG(status) == SIGINT))
		status = 130;
	else
		status = WEXITSTATUS(status);
	tree = parsepipeline(buf, status);
	if (!tree)
		return (0);
	match(*buf, "");
	if (**buf)
	{
		printf("Invalid Command");
		return (NULL);
	}
	return (tree);
}

t_tree	*parsepipeline(char **buf, int status)
{
	t_tree	*tree;

	tree = parsecmd(buf, status);
	if (!tree)
		return (0);
	if (match(*buf, "|"))
	{
		if (!*(((t_cmdtree *)tree)-> cmd))
		{
			printf("Syntax error near unexpected token '|'\n");
			freetree(tree);
			return (0);
		}
		consume(buf, NULL, NULL);
		tree = con_pipetree(tree, parsepipeline(buf, status));
	}
	return (tree);
}

char	*utilcmdandredir(char *sarg, char *earg, int status)
{
	char	*word;
	char	*updword;

	word = getstr(sarg, earg);
	updword = handleword(word, status);
	free(word);
	return (updword);
}

t_tree	*cmdandredir(t_tree *tree, t_cmdtree *cmdtree, char **buf, int status)
{
	int		i;
	int		tok;
	char	*sarg;
	char	*earg;
	char	*word;

	i = 0;
	while (!match(*buf, "|"))
	{
		tok = consume(buf, &sarg, &earg);
		if (!tok)
			break ;
		word = utilcmdandredir(sarg, earg, status);
		if (!(*word))
			free(word);
		else if (word && *word)
			cmdtree -> cmd[i++] = word;
		tree = parseredir(buf, tree, status);
		if (!tree)
			return (0);
	}
	cmdtree -> cmd[i] = NULL;
	return (tree);
}

t_tree	*parsecmd(char **buf, int status)
{
	t_tree		*tree;
	t_cmdtree	*cmdtree;

	tree = con_cmdtree();
	cmdtree = (t_cmdtree *)tree;
	tree = parseredir(buf, tree, status);
	if (!tree)
		return (0);
	tree = cmdandredir(tree, cmdtree, buf, status);
	return (tree);
}
