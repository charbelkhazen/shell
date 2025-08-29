/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkhazen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:21:28 by chkhazen          #+#    #+#             */
/*   Updated: 2025/08/29 16:15:00 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*parseprogram(char **buf, int status)
{
	t_tree	*tree;

	if (globsig == SIGINT)
	{
		globsig = 0;
		status = 128 + SIGINT;
	}
	else
		status = WEXITSTATUS(status);
	tree = parsepipeline(buf, status);
	if (!tree)
		return (0);
	match(*buf, ""); //? JUST SKIP whitespace 
	if (**buf)
	{
		printf("Invalid Command"); // HANDLE CORRECTLY
		return (NULL);
		//exit(127); //ASAS
	}
	return (tree);
}

t_tree *parsepipeline(char **buf, int status)
{
	t_tree	*tree;

	tree = parsecmd(buf, status);
	if (!tree)
		return (0); //added 
	if (match(*buf, "|"))
	{
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
	int	i;
	int	tok;
	char	*sarg;
	char	*earg;
	char	*word;

	i = 0;
	while (!match(*buf, "|"))
	{
		tok = consume(buf, &sarg, &earg);
		if (!tok)
			break;
		word = utilcmdandredir(sarg, earg, status);
		if (!(*word))
			free(word);
		else if (word && *word)
		{
			cmdtree -> cmd[i] = word;
			i++;
		}
		tree = parseredir(buf, tree, status);
		if (!tree)
			return (0);
	}
	cmdtree -> cmd[i] = NULL;
	return (tree);
}

t_tree	*parsecmd(char **buf, int status)
{
	t_tree	*tree;
	t_cmdtree	*cmdtree;

	tree = con_cmdtree();
	cmdtree = (t_cmdtree *)tree;
	tree = parseredir(buf, tree, status);
	if (!tree)
		return (0); //added
	tree = cmdandredir(tree, cmdtree, buf, status);
	return (tree);
}

t_tree	*parseredir(char **buf, t_tree *tree, int status)
{
	int		redir;
	char	*startfn;
	char	*endfn;
	char	*filename;
	t_tree **tail = &tree;
	while ((*tail)->type == '<' || (*tail)->type == '>'|| (*tail)->type == 'h'|| (*tail)->type == 'a')
		tail = &((t_redirtree*)*tail)->cmd;
	while (match(*buf, "><"))
	{
		redir = consume(buf, NULL, NULL);
		if (consume(buf, &startfn, &endfn) != 'w')
		{
			printf("Syntax error near unexpected token 'newline'\n"); //FIX
			return (NULL);
			//exit(2); //activated in echo $< -> not ASAS
		}
		filename = getstr(startfn, endfn);
		//tree = con_redirtree(tree, redir, filename);
		*tail = con_redirtree(*tail, redir, filename);
		tail = &((t_redirtree *)*tail)-> cmd;
	}
	return (tree);
}

void	printtree(t_tree *tree)
{
	if (tree -> type == 'w')
	{
		t_cmdtree *cmdtree = (t_cmdtree *)tree;
		char	**argv = cmdtree -> cmd;
		while (*(argv))
			argv ++;
	}
	else if (tree -> type == '|')
	{
		t_pipetree *pipetree = (t_pipetree *)tree;
		printf("(");
		printtree(pipetree -> right);
		printf(" | ");
		printtree(pipetree -> left);
		printf(")");
	}
	else if ((tree -> type == '>') || (tree -> type == '<') || (tree -> type == 'a') || (tree -> type == 'h'))
	{
		t_redirtree *redirtree = (t_redirtree *) tree;
		printf("( redir %s ", redirtree -> file_name);
		printtree(redirtree -> cmd);
		printf(")");
	}
}

void	freetree(t_tree *tree)
{
	t_pipetree	*pipetree;
	t_redirtree	*redirtree;
	t_cmdtree	*cmdtree;
	char	**argv;

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
	{
		pipetree = (t_pipetree *)tree;	
		freetree(pipetree -> right);
		freetree(pipetree -> left);
		free(pipetree);
	}
	else if ((tree -> type == '>') || (tree -> type == '<') || (tree -> type == 'a') || (tree -> type == 'h'))
	{
		redirtree = (t_redirtree *)tree;	
		freetree(redirtree -> cmd);
		free(redirtree -> file_name);
		free(redirtree);
	}
}

/*
int globsig =0;
int main()
{
	//char *buf = "echo\"fewrfe$HOME\" bbye | echo < file sdsd < file1 ok ok ok | $ASASSA bye$ $HOME";
	char *buf = "$hihihi | ls | 'echo $?' | $hhhh $home $HOME $$$";
	t_tree *result = parseprogram(&buf, 0);
	freetree(result);
}
*/
