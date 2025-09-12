#include "minishell.h"

char    *ft_getenv(char *var, char **env)
{
        int     i;
        int     sizevar;
	char	*val;

        if (!var || !(*var) || !env)
                return (0);
        sizevar = (int)ft_strlen(var);
        i = 0;
        while (env[i])
        {
                if (!ft_strncmp(var, env[i], sizevar) && ((*(env[i] + sizevar) == '=') || (*(env[i] + sizevar) == 0)))
		{
			val = (ft_strchr(env[i], '=') + 1);
			if (val)
				return (val); 
			printf("sdsd");
			return (0);
		}
                i ++;
        }
        return (0);
}

int main(int ac, char *av[], char *env[])
{
	char *s = ft_getenv("hi", env);
	if (s)
		printf("%s\n", s);
	else
		printf("NULL\n");
}

/*   

int	getword(char **buf, char **word, char ***env, int status)
{
	char	*tempword;
	char	*sarg;
	char	*earg;

	if(!consume(buf, &sarg, &earg))
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

t_tree  *parsecmd(char **buf, int status, char ***env)
{
        t_tree          *tree;
        t_cmdtree       *cmdtree;
        int             i;
        char    *word;

        tree = con_cmdtree();
        cmdtree = (t_cmdtree *)tree;
        tree = parseredir(buf, tree, status);
        if (!tree)
                return (0);
        i = 0;
        while (!match(*buf, "|"))
        {
        	if (!getword(buf, &word, env, status))
        		break;
        	else if (word)
                        cmdtree->cmd[i++] = word;
                tree = parseredir(buf, tree, status);
                if (!tree)
                        return (0);
        }
        cmdtree->cmd[i] = NULL;
        return (tree);
}
*/