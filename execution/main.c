/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:10:14 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/26 06:50:18 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmds(t_cmd *tavern, char **env, t_env **envr)
{
	int		pipfd[2];
	int		v;
	pid_t	pid1;
	int		fd;

	fd = dup(STDIN_FILENO);
	if (tavern->next == NULL)
	{
		// printf("Single Command\n");
		pid1 = fork();
		if (pid1 == 0)
		{
			v = 0;
			if (if_builting(tavern, envr))
			{
				// puts("builted");
				v = 1;
			}
			if (v == 0)
			{
				// puts("not builted");
				single_cmd_exec(tavern, env);
			}
		}
	}
	else
	{
		while (tavern)
		{
			if (pipe(pipfd) == -1)
				error_out("pipe", 0);
			pid1 = fork();
			if (pid1 == 0)
			{
				v = 0;
				if (tavern->next)
				{
					if (dup2(pipfd[1], STDOUT_FILENO) < 0)
					{
						printf("[1]\n");
						error_out("dup2", 0);
					}
					close(pipfd[1]);
				}
				if (if_builting(tavern, envr))
					v = 1;
				else if (v == 0)
					execute_command(tavern, env);
			}
			if (dup2(pipfd[0], STDIN_FILENO) < 0)
			{
				printf("[2]\n");
				error_out("dup2", 0);
			}
			close(pipfd[0]);
			close(pipfd[1]);
			tavern = tavern->next;
		}
	}
	waiting_und_closing(pid1);
	puts("closing");
	if (dup2(fd, STDIN_FILENO))
	{
		printf("[3]\n");
		error_out("dup2", 0);
	}
	close(fd);
}

int	if_builting(t_cmd *tavern, t_env **env)
{
	if (ft_strcmp(tavern->cmd[0], "echo") == 0)
	{
		check_redirections(tavern);
		return (echo_builted(tavern), 1);
	}
	if (ft_strcmp(tavern->cmd[0], "cd") == 0)
	{
		check_redirections(tavern);
		return (cd_builted(tavern, env), 1);
	}
	else if (ft_strcmp(tavern->cmd[0], "pwd") == 0)
	{
		check_redirections(tavern);
		return (print_working_directory(), 1);
	}
	else if (ft_strcmp(tavern->cmd[0], "export") == 0)
	{
		check_redirections(tavern);
		return (ft_export(tavern, env), 1);
	}
	else if (ft_strcmp(tavern->cmd[0], "unset") == 0)
	{
		check_redirections(tavern);
		return (ft_unset(tavern, *env), 1);
	}
	else if (ft_strcmp(tavern->cmd[0], "env") == 0)
	{
		check_redirections(tavern);
		return (ft_env(env), 1);
	}
	else if (ft_strcmp(tavern->cmd[0], "exit") == 0)
	{
		check_redirections(tavern);
		return (ft_exit(tavern), 1);
	}
	return (0);
}

void	execute_command(t_cmd *tavern, char **env)
{
	char	**path;
	int		ret;
	int		i;

	check_redirections(tavern);
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], tavern->cmd[0], 1);
	i = command_search(path);
	ret = execve(path[i], tavern->cmd, env);
	if (ret == -1)
		error_out("execve", 0);
}

void	single_cmd_exec(t_cmd *tavern, char **env)
{
	char	**path;
	int		ret;
	int		i;

	if (tavern->fd_in != 0)
	{
		if (dup2(tavern->fd_in, STDIN_FILENO) < 0)
			error_out("dup2", 0);
		close(tavern->fd_in);
	}
	if (tavern->fd_out != 1)
	{
		if (dup2(tavern->fd_out, STDOUT_FILENO) < 0)
			error_out("dup2", 0);
		close(tavern->fd_out);
	}
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], tavern->cmd[0], 1);
	i = command_search(path);
	ret = execve(path[i], tavern->cmd, NULL);
	if (ret == -1)
		error_out("execve", 0);
}

void	waiting_und_closing(pid_t pid1)
{
	waitpid(pid1, NULL, 0);
}
