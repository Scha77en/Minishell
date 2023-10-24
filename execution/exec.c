/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:10:14 by aouhbi            #+#    #+#             */
/*   Updated: 2023/10/21 18:15:17 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*execute_cmds(t_cmd **tavern, char **env, t_env **envr, char *pwd)
{
	int		pipfd[2];
	// int		v;
	pid_t	pid1 = -1;
   	// pid_t terminatedPid;
	int		for_next = 0;

	// v = 0;
	if ((*tavern)->next == NULL)
	{
		if (if_builting(tavern, envr, &pwd))
				;
		else
		{
			pid1 = fork();
			if (pid1 == 0)
				single_cmd_exec((*tavern), env, envr);
		}
	}
	else
	{
		while ((*tavern))
		{
			if ((*tavern)->next && pipe(pipfd) == -1)
				error_out("pipe", 0);
			pid1 = fork();
			if (pid1 == 0)
			{
				if ((*tavern)->next)
				{
					if (dup2(pipfd[1], STDOUT_FILENO) < 0)
						error_out("dup2 ", 0);
					close(pipfd[1]);
					close(pipfd[0]);
				}
				if (for_next)
				{
					if (dup2(for_next, STDIN_FILENO) < 0)
						error_out("dup2", 0);
					close(for_next);
				}
				if (if_builting(tavern, envr, &pwd))
					exit(0);
				execute_command((*tavern), env);
			}
			if (for_next)
				close(for_next);
			if ((*tavern)->next)
			{
				close(pipfd[1]);
				for_next = pipfd[0];
			}
			*tavern = (*tavern)->next;
		}
	}
	while (wait(NULL) > 0)
	{
 		// terminatedPid = wait(&g_status);
 		if (WIFEXITED(g_status)) {
			// Child process exited normally
 	    	g_status = WEXITSTATUS(g_status);
 		}
		else
		{
			// Child process exited abnormally
			g_status = WTERMSIG(g_status);
		}
	}
	return (pwd);
}

int	if_builting(t_cmd **tavern, t_env **env, char **pwd)
{
	if (ft_strcmp((*tavern)->cmd[0], "echo") == 0)
		return (echo_builted((*tavern)), 1);
	if (ft_strcmp((*tavern)->cmd[0], "cd") == 0)
		return (cd_builted(tavern, env, pwd), 1);
	else if (ft_strcmp((*tavern)->cmd[0], "pwd") == 0)
		return (print_working_directory(tavern, pwd), 1);
	else if (ft_strcmp((*tavern)->cmd[0], "export") == 0)
		return (ft_export((*tavern), env), 1);
	else if (ft_strcmp((*tavern)->cmd[0], "unset") == 0)
		return (ft_unset((*tavern), env), 1);
	else if (ft_strcmp((*tavern)->cmd[0], "env") == 0)
		return (ft_env(env, 0), 1);
	else if (ft_strcmp((*tavern)->cmd[0], "exit") == 0)
		return (ft_exit((*tavern)), 1);
	else if (ft_strcmp((*tavern)->cmd[0], "$?") == 0)
		return (printf("%d\n", g_status), 1);
	return (0);
}

void	execute_command(t_cmd *tavern, char **env)
{
	char	**path;
	int		ret;
	int		i;

	check_redirections(tavern);
	if (access(tavern->cmd[0], F_OK) == 0)
	{
		ret = execve(tavern->cmd[0], tavern->cmd, env);
		if (ret == -1)
		{
			error_out("execve", 0);
			g_status = 126;
			exit(126);
		}
	}
	else
	{
		path = find_path(env);
		i = -1;
		while (path[++i])
			path[i] = ft_strjoin_b(path[i], tavern->cmd[0], 1);
		i = command_search(path);
		ret = execve(path[i], tavern->cmd, env);
		if (ret == -1)
		{
			ft_putstr_fd(tavern->cmd[0], 2);
			write(2, ": command not found\n", 20);
			g_status = 127;
			exit(127);
		}
	}
}

void	single_cmd_exec(t_cmd *tavern, char **env, t_env **envr)
{
	char	**path;
	int		ret;
	int		i;

	(void)envr;
	ret = 0;
	check_redirections(tavern);
	if (access(tavern->cmd[0], F_OK) == 0)
	{
		ret = execve(tavern->cmd[0], tavern->cmd, env);
		if (ret == -1)
		{
			error_out("execve", 0);
			g_status = 126;
			exit(126);
		}
	}
	else
	{
		path = find_path(env);
		i = -1;
		while (path[++i])
			path[i] = ft_strjoin_b(path[i], tavern->cmd[0], 1);
		i = command_search(path);
		ret = execve(path[i], tavern->cmd, env);
		if (ret == -1)
		{
			ft_putstr_fd(tavern->cmd[0], 2);
			write(2, ": command not found\n", 20);
			g_status = 127;
			exit(127);
		}
	}
}





// fix the single builting redirection doesnt reset when finishes; pwd > OKOK; echo | cat -e; !--DONE--! => solved but created a new problem, cat | cat | ls; --DONE--

// echo -nnnnnnnn protection; --DONE--

// echo - n skips the '-' in my program and it shouldn't, fix that. --DONE--

// unset and export with alphabics and numbers procetction, only alphabics and _ is allowed first, after the first numerics are also allowed in the followings; --DONE--

// the split in the export should be splitting with one = only and not more; --DONE--

// pwd if failed, get the path from the satitc variable you saved into it ealier in the main; also if the path is changed, change the static variable; --DONE--
// Hint : whenever u call chdir() in "cd" change the PWD value to what chdir is changing to. --DONE--
// when you do cd, if the path is not found, dont change the PWD; --DONE--

// Note: the evaluator may unset the env from the start with "./minishell env -i" command
// check if env is NULL first, if true, add the necessary ones, PATH=, PWD=, SHELLLVL=, _=. --DONE--

// add the signals and handle them; --DONE--

// only the 0,1,2 should be remaining after every command, the rest should be closed; --DONE--


/***************************************************************************************************************************************************************************************************/


// 1- handle when executing minishell inside minishell, the shell level must be incremented in the env, and will only exit from the main minishell if it reaches the smallest amount;

// 2- when exporting a variable without a value (which means without '=' sign), it should not be added in the env, but it will be available when executing export;

// 3- set the garbage collector;

// 4- sort the envirement when you print it with export only;

// 5- handle when the PATH is unseted; the result should be fixed;

// 6- error_out must write the msg in the fd_out.


// 7-
// minishell$ $USER
// Schatten: command not found "expected"
// execve: Bad address "result"

// minishell$ $HOME
// minishell: /home/Schatten: Is a directory "expected"
// execve: Bad address "result"

// ./minishell + an argument should return for example :
// ./minishell config:
// minishell: config: No such file or directory
// ./minishell ls
// /bin/ls: /bin/ls: cannot execute binary file

// while true; do lsof -c minishell; done
// while true; do leaks minishell; done