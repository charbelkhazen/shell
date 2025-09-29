/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:37:54 by jissa             #+#    #+#             */
/*   Updated: 2025/09/29 13:07:21 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "limits.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>

extern int	g_globsig;

typedef struct s_tree
{
	int	type;
}	t_tree;

typedef struct s_cmdtree
{
	int		type;
	char	*cmd[100];
}	t_cmdtree;

typedef struct s_redirtree
{
	int		type;
	t_tree	*cmd;
	char	*file_name;
	int		fd;
	int		option;
}	t_redirtree;

typedef struct s_pipetree
{
	int		type;
	t_tree	*right;
	t_tree	*left;
}	t_pipetree;

typedef struct s_modifiable
{
	char	*start;
	char	*exp;
	char	*endexp;
	char	*env;
	int		steps;
	char	*endmod;
}	t_modifiable;

typedef struct s_mod
{
	char	*start;
	char	*obj;
	char	*eobj;
	int		steps;
}	t_mod;

int				match(char *ptr, char *tok);
int				consume(char **curr, char **tok, char **endtok);
char			*getstr(char *start, char *end);
t_tree			*con_redirtree(t_tree *cmd, int type, char *fn);
t_tree			*con_pipetree(t_tree *left, t_tree *right);
t_tree			*con_cmdtree(void);
char			*towhitespace(char *ptr);
void			mergeremain(char *merge, t_modifiable *mod);
t_modifiable	*con_modifiable(char *cmd, char *exp);
t_modifiable	*modify(t_modifiable *mod, int status, char ***envp);
t_modifiable	*expandbuff(char *cmd, int status, char ***envp);
char			*applyexp(char *cmd, int type, int status, char ***envp);
char			*find_full_path(char *command, char *path);
char			*get_path(char **env);
void			trav_tree(t_tree *tree, char ***envp, int *status);
void			exec_input_redir(t_redirtree *tree, char ***env, int *status);
void			exec_heredoc(t_redirtree *tree, char ***env, int *status);
void			exec_pipe(t_pipetree *tree, char ***envp, int *status);
void			exec_command_node(t_cmdtree *cmd, char ***env, int *status);
int				unset_builtin(char **args, char ***env);
int				export_builtin(char **args, char ***envp);
int				exit_builtin(char **args, char **envp, \
int startflag, int oldstatus);
int				echo(char **args);
int				only_n_flags(char *input);
int				environment(char **args, char **env);
int				pwd(char **args, char **envp);
int				change_directory(char **args, char ***env);
void			freetree(t_tree *tree);
t_tree			*parseredir(char **buf, t_tree *tree, int status);
t_tree			*parsecmd(char **buf, int status, char ***env);
t_tree			*parsepipeline(char **buf, int status, char ***env);
t_tree			*parseprogram(char **buf, int status, char ***env);
int				ft_strcmp(char *s1, char *s2);
char			*tononalnum(char *ptr);
int				travword(char **cur, char **start, char **end);
char			*handleword(char *buf, int status, char ***envp);
char			*join_free(char *a, char *b);
char			*expand_slice(char *tmp, int tok, int status, char ***envp);
char			*skipwhitespace(char *ptr);
int				isexit(char *s);
int				applybuiltin(char *input, char ***envp, int oldstatus);
void			setsig(int sig);
int				startbuiltin(char *s);
int				chariswhitespace(char s);
char			isquote(char *str);
void			writeexpinput(char *buf, int *pipefd, char ***env);
char			*removequotes(char *str, int *flag);
int				is_numeric(const char *str);
long long		ft_atoll(const char *str);
void			freeshlvl(char **my_env);
void			free_args(char **args);
char			**dupenv(char **envp);
void			handle_exportcmd(char **envp);
void			freeenv(char **env);
char			**findinenv(char *args, char **env);
void			consumepipe(int *token, char **curr);
int				ft_iswhitespace(char *s);
int				iscd(char *s);
int				isexport(char *s);
int				isunset(char *s);
int				startbuiltin(char *s);
void			free_args(char **args);
void			replaceinenv(char *arg, char **foundenv);
int				validatearg(char *arg);
void			handle_exportcmd(char **envp);
void			basicsetup(int *status, char ***envp);
void			launchprgm(char **input, char **tempinput, \
char ***envp, int *status);
char			*ft_getenv(char *var, char **env);
void			addinenv(char *arg, char ***env);
void			sort_envp(char **envp);
void			add_quotes(char **envp);
int				check_quotes(char **envp);
int				unclosedquotes(char *input);
int				handle_input(char *input, char ***env, int *status);
void			handlestartbuiltin(char *input, char ***envp, int *status);
char			**get_args(char *input, int status, char ***env);
void			util_get_args(char *input, char **args, \
int status, char ***env);

#endif
