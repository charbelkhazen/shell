#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
int main()
{
	printf("%d", WEXITSTATUS(127));
}

