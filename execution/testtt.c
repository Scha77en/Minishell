#include "../includes/minishell.h"

int main(void)
{
	int i = 6;

	printf("Hello, \"%d\" World!\n", i);
}

void child_change(t_cmd **tavern)
{
	(*tavern)->fd_in = 4;
}
