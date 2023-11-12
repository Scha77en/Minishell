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
	g_status = 130;
}

void	sigint_exec(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_status = 130;
}

void    herdoc_sigint(int sig)
{
    (void)sig;
	write(1, "\n", 1);
    exit(130);
}

void	handle_sigquit(int sig)
{
    (void)sig;
    write(1, "Quit: 3\n", 8);
    g_status = 131;
}
