#include "minishell.h"

int main(int ac, char *av[], char *ev[])
{
	execve("/bin/ls", av, ev);
}
