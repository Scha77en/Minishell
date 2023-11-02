#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
    g_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void    herdoc_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    g_status = 130;
    return ;
}

void    hang_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    g_status = 130;
    return ;
}

void	handle_sigquit(int sig)
{
    (void)sig;
    write(1, "\b\b  \b\b", 6);
}

void	handle_sigint_child(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(0);
}

void	handle_sigquit_child(int sig)
{
    (void)sig;
    write(1, "Quit: 3\n", 8);
    exit(0);
}

// void    updatexitstatus(int status)
// {
//     g_status = status;
// }
