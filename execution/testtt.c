#include "../includes/minishell.h"

int main(void)
{
	int		v = 0;
	t_cmd	*tavern;
	pid_t	pid1;

	tavern->fd_in = 0;
	pid1 = fork();
	if (pid1 == 0)
		child_change(&tavern);
	if (pid1 == 0)
	{
		printf("child process : %d\n", tavern->fd_in);
	}
	if (pid1 != 0)
		printf("main process = %d\n", tavern->fd_in);
	return(0);
}

void child_change(t_cmd **tavern)
{
	(*tavern)->fd_in = 4;
}
