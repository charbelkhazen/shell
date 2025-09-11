#include "minishell.h"

char    *ft_getenv(char *var, char **env)
{
        int     i;
        int     sizevar;

        if (!var || !(*var) || !env)
                return (0);
        sizevar = (int)ft_strlen(var);
        i = 0;
        while (env[i])
        {
                if (!ft_strncmp(var, env[i], sizevar) && ((*(env[i] + sizevar) == '=') || (*(env[i] + sizevar) == 0)))
                        return (ft_strchr(env[i], '=') + 1);
                i ++;
        }
        return (0);
}

int main(int ac, char *av[], char *env[])
{
	char *s = ft_getenv("USER", env);
	if (s)
		printf("%s\n", s);
	else
		printf("NULL\n");
}
