/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:10:14 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/25 10:32:50 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmds(t_cmd *tavern, char **env, t_env **envr)
{
	int		pipfd[2];
	int		v;
	pid_t	pid1;
	int		l_size;
	int		fd;

	v = 0;
	fd = dup(STDIN_FILENO);
	if (tavern->next == NULL)
	{
		printf("Single Command\n");
		if (if_builting(tavern, envr))
		{
			puts("builted");
			v = 1;
		}
		pid1 = fork();
		if (v == 0 && pid1 == 0)
		{
			puts("not builted");
			single_cmd_exec(tavern, env);
		}
	}
	else
	{
		l_size = ft_lstsize(tavern);
		while (tavern)
		{
			if (if_builting(tavern, envr))
				v = 1;
			else if (v == 0)
			{
				if (pipe(pipfd) == -1)
					error_out("pipe", 0);
				pid1 = fork();
				if (pid1 == 0)
				{
					if (tavern->next)
					{
						if (dup2(pipfd[1], STDOUT_FILENO) < 0)
							error_out("dup2", 0);
						close(pipfd[0]);
						close(pipfd[1]);
					}
					execute_command(tavern, env);
				}
				if (dup2(pipfd[0], STDIN_FILENO) < 0)
					error_out("dup2", 0);
				close(pipfd[0]);
				close(pipfd[1]);
				tavern = tavern->next;
			}
			v = 0;
		}
	}
	waiting_und_closing(pid1, pipfd);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int	if_builting(t_cmd *tavern, t_env **env)
{
	// if (ft_strcmp(tavern->cmd[0], "echo") == 0)
	// 	return (ft_echo(tavern, env), 1);
	if (ft_strcmp(tavern->cmd[0], "cd") == 0)
		return (cd_builted(tavern, env), 1);
	else if (ft_strcmp(tavern->cmd[0], "pwd") == 0)
		return (print_working_directory(), 1);
	// else if (ft_strcmp(tavern->cmd[0], "export") == 0)
		// return (ft_export(tavern, env), 1);
	else if (ft_strcmp(tavern->cmd[0], "unset") == 0)
		return (ft_unset(tavern, *env), 1);
	else if (ft_strcmp(tavern->cmd[0], "env") == 0)
		return (ft_env(*env), 1);
	// else if (ft_strcmp(tavern->cmd[0], "exit") == 0)
		// return (ft_exit(tavern, env), 1);
	return (0);
}

void	execute_command(t_cmd *tavern, char **env)
{
	char	**path;
	int		ret;
	int		i;

	if (tavern->fd_in != 0)
	{
		if (dup2(tavern->fd_in, STDIN_FILENO) < 0)
			error_out("dup2", 0);
	}
	if (tavern->fd_out != 1)
	{
		if (dup2(tavern->fd_out, STDOUT_FILENO) < 0)
			error_out("dup2", 0);
	}
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

	// int		fd2;
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

void	waiting_und_closing(pid_t pid1, int *pipfd)
{
	close(pipfd[1]);
	close(pipfd[0]);
	waitpid(pid1, NULL, 0);
}
