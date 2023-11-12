#include "../includes/minishell.h"

void    ignore_sig(int sig)
{
    (void)sig;
    return ;
}

void	handle_sigint(int sig)
{
	(void)sig;
    write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
}

void	sigint_exec(int sig)
{
	write(1, "\n", 1);
	g_status = 128 + sig;
}

void    herdoc_sigint(int sig)
{
    (void)sig;
	write(1, "\n", 1);
    exit(128 + sig);
}

void	handle_sigquit(int sig)
{
    write(1, "Quit: 3\n", 8);
    g_status = 128 + sig;
}
