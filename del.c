#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
int main()
{
	int	tok;
	char	*sword;
	char	*eword;
	char	*word;

	char input[20] = "hello $USER !";
	char *buf = input;
	tok = 1;
	while (!tok)
	{
		tok = consume(&buf, &sword, &eword);
		word = handleword(getstr(sword, eword), 0);
		while (*word)
		{
			write(1, word, 1);
			word ++;
		}
	}
}

