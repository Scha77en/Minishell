/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_managment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:18:29 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/18 21:07:21 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	manage_redirection(t_cmd *tavern, int *pipfd, char **env)
// {
// 	if (tavern->rederections->type == 6)
// 		handle_input(tavern, pipfd, env);
// 	else if (tavern->rederections->type == 4)
// 		handle_output(tavern, pipfd, env);
// 	else if (tavern->rederections->type == 5)
// 		handle_append(tavern, pipfd, env);
// }

// void	handle_input(t_cmd *tavern, int *pipfd, char **env)
// {
// 	char	**cmd;
// 	char	**path;
// 	int		ret;
// 	int		i;
// 	int		fd1;

// 	fd1 = open(tavern->rederections->file, O_RDONLY);
// 	if (fd1 == -1)
// 		error_out("open", 0);
// 	close(pipfd[0]);
// 	if (tavern->cmds->next != NULL)
// 	{
// 		if (dup2(pipfd[1], STDOUT_FILENO) < 0)
// 			error_out("dup2", 0);
// 		close(pipfd[1]);
// 	}
// 	if (dup2(fd1, STDIN_FILENO) < 0)
// 		error_out("dup2", 0);
// 	close(fd1);
// 	cmd = ft_split(tavern->cmds->cmd, ' ');
// 	path = find_path(env);
// 	i = -1;
// 	while (path[++i])
// 		path[i] = ft_strjoin_b(path[i], cmd[0], 1);
// 	i = command_search(path);
// 	ret = execve(path[i], cmd, env);
// 	if (ret == -1)
// 		error_out("execve", 0);
// }

// void	handle_output(t_cmd *tavern, int *pipfd, char **env)
// {
// 	char	**cmd;
// 	char	**path;
// 	int		ret;
// 	int		i;
// 	int		fd2;

// 	fd2 = open(tavern->rederections->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
// 	if (fd2 == -1)
// 		error_out("open", 0);
// 	close(pipfd[1]);
// 	if (dup2(pipfd[0], STDIN_FILENO) < 0)
// 		error_out("dup2", 0);
// 	close(pipfd[0]);
// 	if (dup2(fd2, STDOUT_FILENO) < 0)
// 		error_out("dup2", 0);
// 	close(fd2);
// 	cmd = ft_split(tavern->cmds->cmd, ' ');
// 	path = find_path(env);
// 	i = -1;
// 	while (path[++i])
// 		path[i] = ft_strjoin_b(path[i], cmd[0], 1);
// 	i = command_search(path);
// 	ret = execve(path[i], cmd, env);
// 	if (ret == -1)
// 		error_out("execve", 0);
// }

// void	handle_append(t_cmd *tavern, int *pipfd, char **env)
// {
// 	char	**cmd;
// 	char	**path;
// 	int		ret;
// 	int		i;
// 	int		fd3;

// 	fd3 = open(tavern->rederections->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
// 	if (fd3 == -1)
// 		error_out("open", 0);
// 	close(pipfd[1]);
// 	if (dup2(pipfd[0], STDIN_FILENO) < 0)
// 		error_out("dup2", 0);
// 	close(pipfd[0]);
// 	if (dup2(fd3, STDOUT_FILENO) < 0)
// 		error_out("dup2", 0);
// 	close(fd3);
// 	cmd = ft_split(tavern->cmds->cmd, ' ');
// 	path = find_path(env);
// 	i = -1;
// 	while (path[++i])
// 		path[i] = ft_strjoin_b(path[i], cmd[0], 1);
// 	i = command_search(path);
// 	ret = execve(path[i], cmd, env);
// 	if (ret == -1)
// 		error_out("execve", 0);
// }
