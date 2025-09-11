SRCS=expansion/applyexp_1.c expansion/applyexp_2.c builtins/builtin_utils.c builtins/cd.c builtins/environment.c builtins/pwd.c builtins/export1.c builtins/export2.c builtins/unset.c builtins/exit.c builtins/echo.c run_minishell/main1.c run_minishell/main2.c parsing/parsing1.c parsing/parsing2.c tokenization/match_advance1.c tokenization/match_advance2.c constructors/constructors.c execution/commands.c execution/heredoc.c execution/pipes.c execution/redirections.c execution/trav_exec.c execution/finding_path.c minishell_utils/utils1.c minishell_utils/utils2.c minishell_utils/utils3.c minishell_utils/utils4.c handlecmd/handleword.c handlecmd/handleword2.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
LIBFT_A = libft/libft.a

all : $(NAME)
%.o: %.c
	cc -c $< -o $@

$(NAME): $(LIBFT_A) $(OBJS)
	cc $(OBJS) $(LIBFT_A)  -lreadline -g -o $(NAME)

$(LIBFT_A):
	$(MAKE) -C libft

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	        $(MAKE) -C libft fclean
		        rm -f $(NAME)

re : fclean all
