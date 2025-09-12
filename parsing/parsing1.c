/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:59:46 by jissa             #+#    #+#             */
/*   Updated: 2025/09/12 15:33:47 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*parseprogram(char **buf, int status, char ***env)
{
	t_tree	*tree;

	if (g_globsig == SIGINT)
	{
		g_globsig = 0;
		status = 128 + SIGINT;
	}
	else if (!(WIFEXITED(status)) && (WTERMSIG(status) == SIGINT))
		status = 130;
	else
		status = WEXITSTATUS(status);
	tree = parsepipeline(buf, status, env);
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

t_tree	*parsepipeline(char **buf, int status, char ***env)
{
	t_tree	*tree;

	tree = parsecmd(buf, status, env);
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
		tree = con_pipetree(tree, parsepipeline(buf, status, env));
	}
	return (tree);
}

int	getword(char **buf, char **word, char ***env, int status)
{
	char	*tempword;
	char	*sarg;
	char	*earg;

	if (!consume(buf, &sarg, &earg))
		return (0);
	tempword = getstr(sarg, earg);
	*word = handleword(tempword, status, env);
	if (tempword)
		free(tempword);
	if (*word && !(**word))
	{
		free(*word);
		*word = 0;
	}
	return (1);
}

t_tree	*parsecmd(char **buf, int status, char ***env)
{
	t_tree		*tree;
	t_cmdtree	*cmdtree;
	int			i;
	char		*word;

	tree = con_cmdtree();
	cmdtree = (t_cmdtree *)tree;
	tree = parseredir(buf, tree, status);
	if (!tree)
		return (0);
	i = 0;
	while (!match(*buf, "|"))
	{
		if (!getword(buf, &word, env, status))
			break ;
		else if (word)
			cmdtree->cmd[i++] = word;
		tree = parseredir(buf, tree, status);
		if (!tree)
			return (0);
	}
	cmdtree->cmd[i] = NULL;
	return (tree);
}
