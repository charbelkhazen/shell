/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:44:26 by jissa             #+#    #+#             */
/*   Updated: 2025/09/13 16:24:50 by chkhazen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	runcmd(char **args, char ***env)
{
	if (args[0] && ft_strcmp(args[0], "cd") == 0)
		return (change_directory(args, *env));
	else if (args[0] && ft_strcmp(args[0], "pwd") == 0)
		return (pwd(args, *env));
	else if (args[0] && ft_strcmp(args[0], "env") == 0)
		return (environment(args, *env));
	else if (args[0] && ft_strcmp(args[0], "echo") == 0)
		return (echo(args));
	else if (args[0] && ft_strcmp(args[0], "exit") == 0)
		return (exit_builtin(args, *env, 0));
	else if (args[0] && ft_strcmp(args[0], "export") == 0)
		return (export_builtin(args, env));
	else if (args[0] && ft_strcmp(args[0], "unset") == 0)
		return (unset_builtin(args, env));
	return (-1);
}

int	isbuiltin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || \
ft_strcmp(cmd, "pwd") == 0 || \
ft_strcmp(cmd, "env") == 0 || \
ft_strcmp(cmd, "echo") == 0 || \
ft_strcmp(cmd, "exit") == 0 || \
ft_strcmp(cmd, "unset") == 0 || \
ft_strcmp(cmd, "export") == 0)
		return (1);
	else
		return (0);
}

void	ifisbuiltin(t_cmdtree *cmd, char ***env)
{
	int	exitruncmd;

	exitruncmd = runcmd(cmd->cmd, env);
	exit(exitruncmd);
}

void	exec_command_node(t_cmdtree *cmd, char ***env, int *status)
{
	char	*full_path;
	char	*path_env;

	(void)status;
	if (!*(cmd -> cmd))
		exit(0);
	if (isbuiltin((cmd->cmd)[0]))
		ifisbuiltin(cmd, env);
	if ((cmd->cmd)[0][0] == '/' || (cmd->cmd)[0][0] == '.')
		full_path = cmd->cmd[0];
	else
	{
		path_env = get_path(*env);
		full_path = find_full_path(cmd->cmd[0], path_env);
	}
	if (full_path)
		execve(full_path, cmd->cmd, *env);
	printf("Command not found\n");
	exit(127);
}
