/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:15:52 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/13 10:58:27 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	subshell(t_cmd **tavern, t_env **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execute_shell((*tavern), env);
}

void	execute_shell(t_cmd *tavern, t_env **env)
{
	char	**u_env;
	int		ret;

	u_env = update_env(env);
	check_redirections(tavern);
	if (access(tavern->cmd[0], F_OK) == 0)
	{
		ret = execve(tavern->cmd[0], tavern->cmd, u_env);
		if (ret == -1)
			command_not_found(tavern);
	}
	else
		exec_with_path(tavern, u_env);
}

void	execute_command(t_cmd *tavern, t_env **envr)
{
	char	**u_env;
	int		ret;

	signal(SIGINT, sigint_exec);
	u_env = update_env(envr);
	check_redirections(tavern);
	if (ft_strncmp(tavern->cmd[0], "/", 1) == 0
		&& access(tavern->cmd[0], F_OK) == 0)
	{
		ret = execve(tavern->cmd[0], tavern->cmd, u_env);
		if (ret == -1)
			command_not_found(tavern);
	}
	else
		exec_with_path(tavern, u_env);
}

void	exec_with_path(t_cmd *tavern, char **u_env)
{
	char	**path;
	int		ret;
	int		i;

	path = find_path(u_env);
	if (path == NULL)
		no_such_file(tavern);
	ret = 0;
	i = -1;
	while (path && path[++i])
		path[i] = ft_strjoin_b(path[i], tavern->cmd[0], 1);
	i = command_search(path);
	if (i == -1)
		path[++i] = NULL;
	ret = path_backslash(tavern->cmd[0]);
	if (ret == -1)
		no_such_file(tavern);
	ret = execve(path[i], tavern->cmd, u_env);
	if (ret == -1)
		command_not_found(tavern);
}

int	path_backslash(char *path)
{
	int		i;

	i = 0;
	if (!path)
		return (-1);
	while (path[i])
	{
		if (path[i] == '/')
			return (-1);
		i++;
	}
	return (0);
}
