#include "minishell.h"

int	validatearg(char *arg)
{
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

int	isinenv(char *arg, char **env)
{
	char	*var;
	int	varsize;
	char	*equalptr;

	equalptr = ft_strchr(arg, '=');
	if (equalptr)
		var = getstr(arg, equalptr);
	else
		var = ft_strdup(arg);
	varsize = ft_strlen(var);
	while (*env)
	{
		if (ft_strncmp(*env, var, varsize) && (*(*env + varsize) == '=' || *(*env + varsize) == 0)) 
			return (1);
	}
		
}

void	applyexport(char *arg, char **env)
{

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
			applyexport(*args, env);
		args ++;
	}
}

