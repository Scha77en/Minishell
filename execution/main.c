/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:10:14 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/26 11:43:28 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmds(t_cmd *tavern, char **env)
{
	int		pipfd[2];
	// int		j;
	// t_cmd	*current;
	pid_t	pid1;
	pid_t	pid2 = -1;

	if (pipe(pipfd) == -1)
		error_out("pipe", 0);
	// current = tavern;
	// while(1)
	// {
	// // if (current == NULL)
	// // 	printf("Current is NULL");
	// 	printf("__%s__\n", current->cmd[0]);
	// 	current = current->next;
	// 	if (current == NULL)
	// 		break ;
	// }
	// while(1);
	if (tavern->next == NULL)
	{
		printf("ENTERED\n");
		pid1 = fork();
		if (pid1 == 0)
			single_cmd_exec(tavern, env);
	
	}
	// while(1);
	else
	{
		while (tavern)
		{
			pid1 = fork();
			if (pid1 == 0)
				execute_command(tavern, pipfd, env);
			else
				wait(0);
			if (tavern->next)
			{
				// printf("redirecting stdin to pipefd[0]\n");
				if (dup2(pipfd[0], STDIN_FILENO) < 0)
					error_out("dup2", 0);
				close(pipfd[1]);
				close(pipfd[0]);
			}
			tavern = tavern->next;
		}
	}
	waiting_und_closing(pid1, pid2, pipfd);
}

void	execute_command(t_cmd *tavern, int *pipfd, char **env)
{
	char	**path;
	int		ret;
	int		i;

	if (tavern->next)
	{
		// printf("redirecting stdout to pipefd[1]\n");
		if (dup2(pipfd[1], STDOUT_FILENO) < 0)
			error_out("dup2", 0);
		close(pipfd[0]);
		close(pipfd[1]);
	}
	if (tavern->fd_in != 0)
	{
		// printf("redirecting stdin to fd_in\n");
		if (dup2(tavern->fd_in, STDIN_FILENO) < 0)
			error_out("dup2", 0);
	}
	close(tavern->fd_in);
	if (tavern->fd_out != 1)
	{
		// printf("redirecting stdout to fd_out\n");
		if (dup2(tavern->fd_out, STDOUT_FILENO) < 0)
			error_out("dup2", 0);
	}
	close(tavern->fd_out);
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], tavern->cmd[0], 1);
	i = command_search(path);
	ret = execve(path[i], tavern->cmd, env);
	if (ret == -1)
		error_out("execve", 0);
}

// void	multiple_cmd_exec(t_cmd *tavern, int *pipfd, char **env)
// {
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	pid1 = fork();
// 	if (pid1 == 0)
// 		manage_first_child(tavern, pipfd, env);
// 	command_handler(tavern, pipfd, env);
// 	pid2 = fork();
// 	if (pid2 == 0)
// 		manage_last_child(tavern, pipfd, env);
// 	else
// 	{
// 		waiting_und_closing(pid1, pid2, pipfd);
// 	}
// }

// void	manage_first_child(t_cmd *tavern, int *pipfd, char **env)
// {
// 	char	**cmd;
// 	char	**path;
// 	int		ret;
// 	int		i;
// 	int		fd1;

// 	close(pipfd[0]);
// 	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
// 		error_out("dup2", 0);
// 	close(pipfd[1]);
// 	cmd = tavern->cmd;
// 	path = find_path(env);
// 	i = -1;
// 	while (path[++i])
// 		path[i] = ft_strjoin_b(path[i], cmd[0], 1);
// 	i = command_search(path);
// 	tavern = tavern->next;
// 	ret = execve(path[i], cmd, env);
// 	if (ret == -1)
// 		error_out("execve", 0);
// }

// void	command_handler(t_cmd *tavern, int *pipfd, char **env)
// {
// 	pid_t	pid_b;

// 	if (tavern->next == NULL)
// 		return ;
// 	while (1)
// 	{
// 		pid_b = fork();
// 		if (pid_b == 0)
// 			manage_children(tavern->cmd, pipfd, env);
// 		else
// 			wait(0);
// 		tavern = tavern->next;
// 		if (tavern->next == NULL)
// 			break ;
// 	}
// }

// void	manage_children(char **cmd, int *pipfd, char **env)
// {
// 	char	**cmd;
// 	char	**path;
// 	int		ret;
// 	int		i;

// 	if (dup2(pipfd[0], STDIN_FILENO) < 0)
// 		error_out("dup2", 0);
// 	close(pipfd[0]);
// 	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
// 		error_out("dup2", 0);
// 	close(pipfd[1]);
// 	path = find_path(env);
// 	i = -1;
// 	while (path[++i])
// 		path[i] = ft_strjoin_b(path[i], cmd[0], 1);
// 	i = command_search(path);
// 	ret = execve(path[i], cmd, env);
// 	if (ret == -1)
// 		error_out("execve", 0);
// }

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
	}
	close(tavern->fd_in);
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
	// printf("\n\t%s\n\n", path[i]);
	// printf("\n\t%s\n\n", cmd[0]);
	ret = execve(path[i], tavern->cmd, NULL);
	if (ret == -1)
		error_out("execve", 0);
}

void	waiting_und_closing(pid_t pid1, pid_t pid2, int *pipfd)
{
	close(pipfd[1]);
	close(pipfd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
