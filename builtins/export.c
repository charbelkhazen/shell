#include "../minishell.h"

void    handle_exportcmd(char **envp)
{
        int     i;

        i = 0;
        while (envp[i])
        {
                printf("declare -x %s\n", envp[i]);
                i++;
        }
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

void	replaceinenv(char *arg, char **foundenv)
{
	char	*temp;

	if (!foundenv || !arg)
		return ;
	temp = *foundenv;
	*foundenv = ft_strdup(arg);
	free(temp);
}

void	freeenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	addinenv(char *arg, char ***env)
{
	int	i;
	char	**temp;

	i = 0;
	while (*(*env + i))
		i++;
	temp = *env;
	*env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (*(temp + i))
	{
		*(*env + i) = ft_strdup(*(temp + i));
		i++;
	}
	*(*env + i) = ft_strdup(arg);
	i++;
	*(*env + i) = 0;
	freeenv(temp);
	printf("env start: %s\n", **env);
}

void	applyexport(char *arg, char ***env)
{
	char	**foundenv;

	foundenv = findinnenv(arg, *env);
	if (ft_strchr(arg, '='))
	{
		if (foundenv)
			replaceinenv(arg, foundenv);
		else
			addinenv(arg, env);
	}
	else
	{
		if (foundenv)
			return;
		else
			addinenv(arg, env);
	}
}

int	export_builtin(char **args, char ***env) //Use handleword() to handle expansions and quotations
{
	int	status;
	char	*var;

	status = 0;
	if (!args[1])
	{
		handle_exportcmd(*env);
		return (0);
	}
	args++;
	while (*args)
	{
		if (!validatearg(*args))
			status = 1;
		else
			applyexport(*args, env);
		args ++;
	}
	return (status);
}
/*
int main(int ac, char *av[], char *envp[])
{
	char **env = dupenv(envp);
	myexport(av, &env);
	int i=0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	freeenv(env);
}
*/
