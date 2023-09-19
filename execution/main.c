/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:10:14 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/17 03:08:53 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmds(t_cmd *tavern, char **env)
{
	int		pipfd[2];
	int		j;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipfd) == -1)
		error_out("pipe", 0);
	// if (final->rederections->type == 1)
	// 	here_doc_management(final, pipfd, env);
	pid1 = fork();
	if (pid1 == 0 && tavern->cmd != NULL && tavern->fd_in == 0 && tavern->fd_out == 1)
		execute_commands(tavern, pipfd, env);
	if (tavern->cmd != NULL && tavern->fd_in != 0 && tavern->out == 1)
		red_in_execute(tavern, pipfd, env);
	else if (pid1 == 0 && final->rederections != NULL)
		manage_redirection(final, pipfd, env);
	command_handler(final, pipfd, env);
	pid2 = fork();
	if (pid2 == 0 && final->rederections == NULL)
		manage_last_child(final->cmds, pipfd, env);
	else if (pid2 == 0 && final->rederections != NULL)
		manage_redirection(final, pipfd, env);
	else
	{
		waiting_und_closing(pid1, pid2, pipfd);
	}
}

void	execute_commands(t_cmd *tavern, int *pipfd, char **env)
{
	if (tavern->next == NULL)
		single_cmd_exec(tavern->cmd, env);
	else
		multiple_cmd_exec(tavern, env);
}

void	manage_first_child(t_cmd *cmds, int *pipfd, char **env)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;
	int		fd1;

	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		error_out("dup2", 0);
	close(pipfd[1]);
	cmd = ft_split(cmds->cmd, ' ');
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0], 1);
	i = command_search(path);
	cmds = cmds->next;
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve", 0);
}

void	command_handler(t_cmd *final, int *pipfd, char **env)
{
	pid_t	pid_b;

	if (final->cmds->next == NULL)
		return ;
	while (1)
	{
		pid_b = fork();
		if (pid_b == 0 && final->rederections == NULL)
			manage_children(final->cmds, pipfd, env);
		if (pid_b == 0 && final->rederections != NULL)
			manage_redirection(final, pipfd, env);
		else
			wait(0);
		final->cmds = final->cmds->next;
		if (final->cmds->next == NULL)
			break ;
	}
}

void	manage_children(t_cmd *cmds, int *pipfd, char **env)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;

	if (dup2(pipfd[0], STDIN_FILENO) < 0)
		error_out("dup2", 0);
	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		error_out("dup2", 0);
	close(pipfd[1]);
	cmd = ft_split(cmds->cmd, ' ');
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0], 1);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve", 0);
}

void	manage_last_child(t_cmd *cmds, int *pipfd, char **env)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;

	close(pipfd[1]);
	if (dup2(pipfd[0], STDIN_FILENO) < 0)
		error_out("dup2", 0);
	close(pipfd[0]);
	cmd = ft_split(cmds->cmd, ' ');
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0], 1);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve", 0);
}

void	single_cmd_exec(char **cmd, char **env)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;
	int		fd2;

	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0], 1);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
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
