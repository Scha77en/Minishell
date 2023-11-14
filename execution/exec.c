/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:10:14 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/14 17:19:36 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*execute_cmds(t_cmd **tavern, t_env **envr, char *pwd)
{
	pid_t	pid1;
	int		status;
	t_cmd	*current;

	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, sigint_exec);
	current = *tavern;
	pid1 = -1;
	status = 0;
	if ((*tavern)->next == NULL)
	{
		if (if_builting(&current, envr, &pwd))
			;
		else
		{
			pid1 = fork();
			if (pid1 == 0)
				execute_command(current, envr);
			else if (pid1 < 0)
				fork_failed();
		}
	}
	else
		multiple_cmds(&current, envr, &pwd, pid1);
	return (waiting_and_signals_handling(status), pwd);
}

void	multiple_cmds(t_cmd **tavern, t_env **envr, char **pwd, pid_t pid1)
{
	int		pipfd[2];
	int		for_next;

	for_next = 0;
	while ((*tavern))
	{
		if ((*tavern)->next && pipe(pipfd) == -1)
		{
			error_out("pipe", 0);
			g_status = 1;
		}
		pid1 = fork();
		if (pid1 == 0)
		{
			pipes_handling(tavern, pipfd, &for_next);
			if (if_builting(tavern, envr, pwd))
				exit(0);
			execute_command((*tavern), envr);
		}
		else if (pid1 < 0)
			fork_failed();
		pipes_closing(tavern, pipfd, &for_next);
		(*tavern) = (*tavern)->next;
	}
}

void	pipes_closing(t_cmd **tavern, int pipfd[2], int *for_next)
{
	if (*for_next)
		close(*for_next);
	if ((*tavern)->next)
	{
		close(pipfd[1]);
		*for_next = pipfd[0];
	}
}

void	pipes_handling(t_cmd **tavern, int pipfd[2], int *for_next)
{
	if ((*tavern)->next)
	{
		if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		{
			error_out("dup2 ", 0);
			exit(1);
		}
		close(pipfd[1]);
		close(pipfd[0]);
	}
	if (*for_next)
	{
		if (dup2(*for_next, STDIN_FILENO) < 0)
		{
			error_out("dup2", 0);
			exit(1);
		}
		close(*for_next);
	}
}

int	if_builting(t_cmd **tavern, t_env **env, char **pwd)
{
	if ((*tavern)->cmd[0] == NULL)
		return (1);
	if (ft_strncmp((*tavern)->cmd[0], "echo", 5) == 0)
		return (echo_builted((*tavern)), g_status = 0, 1);
	if (ft_strncmp((*tavern)->cmd[0], "cd", 3) == 0)
		return (cd_builted(tavern, env, pwd), 1);
	else if (ft_strncmp((*tavern)->cmd[0], "pwd", 4) == 0)
		return (print_working_directory(tavern, pwd), g_status = 0, 1);
	else if (ft_strncmp((*tavern)->cmd[0], "export", 8) == 0)
		return (ft_export((*tavern), env), 1);
	else if (ft_strncmp((*tavern)->cmd[0], "unset", 7) == 0)
		return (ft_unset((*tavern), env), 1);
	else if (ft_strncmp((*tavern)->cmd[0], "env", 4) == 0)
		return (ft_env(tavern, env, 0), 1);
	else if (ft_strncmp((*tavern)->cmd[0], "exit", 6) == 0)
		return (ft_exit((*tavern)), 1);
	else if (ft_strncmp((*tavern)->cmd[0], "./", 2) == 0
		|| ft_strncmp((*tavern)->cmd[0], "../", 1) == 0)
		return (subshell(tavern, env), 1);
	return (0);
}
