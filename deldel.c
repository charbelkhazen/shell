#include "minishell.h"

void moveav(char **av)
{
	av ++;
}

int main(int ac, char *av[])
{
	printf("av:%s\n", *av);
	moveav(av);
	printf("av:%s\n", *av);
}
