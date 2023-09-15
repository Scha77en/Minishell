#include "../includes/minishell.h"

void	error_out(char *msg, int v)
{
	if (v == 0)
		perror(msg);
	if (v == 1)
		write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}
