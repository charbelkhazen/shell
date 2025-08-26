#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
int main()
{
	int	tok;
	char	*sword;
	char	*eword;
	char	*word;
	char	*transword;

	char input[50] = "     hello$USER     !";
	char *buf = input;
	while (*buf)
	{
		if (chariswhitespace(*buf) && *buf)
		{
			write(1, buf, 1);	
			buf ++;
		}
		else
		{
			sword = buf;
			while(!chariswhitespace(*buf) && *buf)
				buf++;
			eword = buf;
			word = getstr(sword, eword);
			transword = handleword(word, 0);
			write(1, word, ft_strlen(word)); 
			free(word);
			free(transword);
		}
	}
}
