/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:10:14 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/28 20:24:50 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmds(t_cmd *tavern, char **env, t_env **envr)
{
	int		pipfd[2];
	int		v;
	pid_t	pid1 = -1;
	int		fd0;
	// int		fd1;

	fd0 = dup(STDIN_FILENO);
	// fd1 = dup(STDOUT_FILENO);
	// printf("fd1 first = %d\n", fd1);
	v = 0;
	if (tavern->next == NULL)
	{
		// printf("Single Command\n");
		
		if (if_builting(tavern, envr))
		{
			v = -1;
		}
		else
		{
			pid1 = fork();
			if (pid1 == 0)
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
			if (tavern->next && pipe(pipfd) == -1)
				error_out("pipe", 0);
			pid1 = fork();
			if (pid1 == 0)
			{
				if (tavern->next)
				{
					if (dup2(pipfd[1], STDOUT_FILENO) < 0)
					{
						printf("[1]\n");
						error_out("dup2 ", 0);
					}
					if (tavern->fd_out == 1)
						tavern->fd_out = pipfd[1];
				}
				if (if_builting(tavern, envr))
					exit(0);
				if (tavern->next)
				{
					close(pipfd[1]);
					close(pipfd[0]);
				}
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
	if (v == 0)
		waiting_und_closing(pid1, pipfd);
	// wait(0);
	// puts("closing");
	// printf("fd1 = %d\n", fd1);
	// printf("fd0 = %d\n", fd0);
	// if (dup2(fd1, STDOUT_FILENO))
	// {
	// 	printf("[7]\n");
	// 	error_out("dup2", 0);
	// }
	if (dup2(fd0, STDIN_FILENO))
	{
		printf("[3]\n");
		error_out("dup2", 0);
	}
	close(fd0);
	// close(fd1);
	close(pipfd[0]);
	while (wait(NULL) > 0)
		;
}

int	if_builting(t_cmd *tavern, t_env **env)
{
	if (ft_strcmp(tavern->cmd[0], "echo") == 0)
	{
		// check_redirections(tavern);
		return (echo_builted(tavern), 1);
	}
	if (ft_strcmp(tavern->cmd[0], "cd") == 0)
	{
		// check_redirections(tavern);
		return (cd_builted(tavern, env), 1);
	}
	else if (ft_strcmp(tavern->cmd[0], "pwd") == 0)
	{
		// check_redirections(tavern);
		return (print_working_directory(tavern), 1);
	}
	else if (ft_strcmp(tavern->cmd[0], "export") == 0)
	{
		// check_redirections(tavern);
		return (ft_export(tavern, env), 1);
	}
	else if (ft_strcmp(tavern->cmd[0], "unset") == 0)
	{
		// check_redirections(tavern);
		return (ft_unset(tavern, env), 1);
	}
	else if (ft_strcmp(tavern->cmd[0], "env") == 0)
	{
		// check_redirections(tavern);
		return (ft_env(env, 0), 1);
	}
	else if (ft_strcmp(tavern->cmd[0], "exit") == 0)
	{
		// check_redirections(tavern);
		return (ft_exit(tavern), 1);
	}
	return (0);
}

void	execute_command(t_cmd *tavern, char **env)
{
	char	**path;
	int		ret;
	int		i;

	printf("regular command\n");
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

	check_redirections(tavern);
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
	close(pipfd[0]);
	close(pipfd[1]);
	waitpid(pid1, NULL, 0);
}







// fix the single builting redirection doesnt reset when finishes; pwd > OKOK; echo | cat -e;

// echo -nnnnnnnn protection; --DONE--

// unset and export with alphabics and numbers procetction, only alphabics and _ is allowed first, after the first numerics are also allowed in the followings;

// pwd if failed, get the path from the satitc variable you saved into it ealier in the main; also if the path is changed, change the static variable;

// when you do cd, if the path is not found, dont change the pwd;

// handle when executing minishell inside minishell, the shell level must be incremented in the env, and will only exit from the main minishell if it reaches the smallest amount;

// sort the envirement when you print it with export only;

// handle when the PATH is unseted; the result should be fixed;

// add the signals and handle them;

// remove the leaks;

// ./minishell + an argument should return for example :
// ./minishell config:
// minishell: config: No such file or directory
// ./minishell ls
// /bin/ls: /bin/ls: cannot execute binary file