#include <stdio.h>
#include <unistd.h>
#include "minishell.h"


void	writeexpinput(char *buf)
{
	int	tok;
	char	*sword;
	char	*eword;
	char	*word;
	char	*transword;

	while (*buf)
	{
		if (chariswhitespace(*buf) && *buf)
			write(1, buf ++, 1);	
		else
		{
			sword = buf;
			while(!chariswhitespace(*buf) && *buf)
				buf++;
			eword = buf;
			word = getstr(sword, eword);
			transword = handleword(word, 0);
			write(1, transword, ft_strlen(transword)); 
			free(word);
			free(transword);
		}
	}
}

int main()
{
	writeexpinput("   hello $USER-- how are you $?");
}
