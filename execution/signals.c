/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:05:35 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/13 15:47:14 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	herdoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

void	handle_sigquit(int sig)
{
	write(1, "Quit: 3\n", 8);
	g_status = 128 + sig;
}

void	waiting_and_signals_handling(int status)
{
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
