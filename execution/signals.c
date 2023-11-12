#include "../includes/minishell.h"

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
//     g_status = 130;
// }

void    ignore_sig(int sig)
{
    (void)sig;
    return ;
}

void	handle_sigint(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_status = 131;
	}
	else if (sig == SIGINT)
	{
        write(1, "\n", 1);
	    rl_on_new_line();
	    rl_replace_line("", 0);
	    rl_redisplay();
		g_status = 130;
	}
}

void    herdoc_sigint(int sig)
{
    (void)sig;
    exit(130);
}

void	handle_sigquit(int sig)
{
    (void)sig;
    write(1, "Quit\n", 5);
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
