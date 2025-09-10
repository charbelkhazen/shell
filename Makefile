LIBFT_A=libft/libft.a

all : uu

$(LIBFT_A):
	$(MAKE) -C libft 

uu:
	cc expansion/applyexp_1.c expansion/applyexp_2.c builtins/builtin_utils.c builtins/cd.c builtins/environment.c builtins/pwd.c builtins/export1.c builtins/export2.c builtins/unset.c builtins/exit.c builtins/echo.c run_minishell/main1.c run_minishell/main2.c parsing/parsing1.c parsing/parsing2.c tokenization/match_advance1.c tokenization/match_advance2.c constructors/constructors.c execution/commands.c execution/heredoc.c execution/pipes.c execution/redirections.c execution/trav_exec.c execution/finding_path.c minishell_utils/utils1.c minishell_utils/utils2.c minishell_utils/utils3.c minishell_utils/utils4.c handlecmd/handleword.c handlecmd/handleword2.c -lreadline
g:
	cc expansion/applyexp_1.c expansion/applyexp_2.c builtins/builtin_utils.c builtins/cd.c builtins/environment.c builtins/pwd.c builtins/export.c builtins/unset.c builtins/exit.c builtins/echo.c main.c parsing.c match_advance.c constructors/constructors.c execution/commands.c execution/heredoc.c execution/pipes.c execution/redirections.c execution/trav_exec.c execution/finding_path.c ft_split.c minishell_utils.c handlecmd/handleword.c handlecmd/handleword2.c -lreadline libft.a -g
del:
	cc del.c builtins.c handlecmd.c match_advance.c applyexp.c  minishell_utils.c libft.a -g
pars:
	cc parsing.c match_advance.c constructors/constructors.c  expansion/applyexp_1.c expansion/applyexp_2.c  handlecmd/handleword.c handlecmd/handleword2.c libft.a
	
hand:
	cc handlecmd.c applyexp.c match_advance.c libft.a
