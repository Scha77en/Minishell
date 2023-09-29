#include "../includes/minishell.h"

int main(void)
{
	int fd;
	int fd0;

	fd0 = dup(STDIN_FILENO);
	fd = dup(STDOUT_FILENO);
	printf("fd0 = %d\n", fd0);
	printf("fd = %d\n", fd);
	if (dup2(fd, STDOUT_FILENO) < 0)
		printf("error\n");
	if (dup2(fd0, STDIN_FILENO) < 0)
		printf("error\n");
	write(fd, "hello\n", 6);
	close(fd);
	close(fd0);
	return (0);
}
