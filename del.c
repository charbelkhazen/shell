#include "minishell.h"

char    *getstr(char *start, char *end) //TODEL
{
        int             len;
        int             i;
        char    *str;

        len = end - start;
        if (len == 0)
                return (0);
        str = malloc(len + 1);
        i = 0;
        while (i < len)
        {
                str[i] = *(start + i);
                i ++;
        }
        str[i] = 0;
        return (str);
}

char    **dupenv(char **envp) //TODEL
{
        int     i;
        char    **dup;

        i = 0;
        while (envp[i])
                i ++;
        dup = malloc(sizeof(char *) * i);
        i = 0;
        while(envp[i])
        {
                dup[i] = envp[i];
                i ++;
        }
        return (dup);
}

int	validatearg(char *arg)
{
	if (!arg)
		return (0);
	if ((*arg != '_') && (!ft_isalpha(*arg)))
		return (0);
	while (*arg && (*arg != '='))
	{
		if ((*arg != '_') && (!ft_isalnum(*arg)))
			return (0);
		arg ++;
	}
	return (1);
}

void	modifyenv(char *arg, char **env)
{
	return ;	
}

void	addenv(char *arg, char **env)
{
	return ;	
}

char	**findinnenv(char *arg, char **env)
{
	char	*var;
	int	varsize;
	char	*equalptr;

	if (!arg || !env)
		return (0);
	equalptr = ft_strchr(arg, '=');
	if (equalptr)
		var = getstr(arg, equalptr);
	else
		var = ft_strdup(arg);
	varsize = ft_strlen(var);
	while (*env)
	{
		if (!ft_strncmp(*env, var, varsize) && (*(*env + varsize) == '=' || *(*env + varsize) == 0)) 
		{
			free(var);
			return (env);
		}
		env++;
	}
	free(var);
	return (0);
}

void	applyexport(char *arg, char **env)
{
	char	**foundenv;

	foundenv = findinnenv(arg, env);
	if (ft_strchr(arg, '='))
	{
		if (foundenv)
			//replaceinenv(arg, foundenv);
		else
			//addinenv(arg, env);
	}
	else
	{
		if (foundenv)
			return;
		else
			addinenv(arg, env);
	}
}

int	myexport(char **args, char **env) //Use handleword() to handle expansions and quotations
{
	int	status;
	char	*var;

	status = 0;
	if (!args[1])
	{
		handle_exportcmd(env);
		return (0);
	}
	args++;
	while (*args)
	{
		if (!validatearg(*args))
			status = 1;
		else
			applyexp(*args, env);
		args ++;
	}
}

int main(int ac, char *av[], char *envp[])
{
	char **env = dupenv(envp);
	printf("validation: %d\n", validatearg(*(av + 1)));
	if (findinnenv(*(av + 1), env))
		printf("found:%s\n", *(findinnenv(*(av + 1), env)));
	free(env);
}
