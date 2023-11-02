/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:10:14 by aouhbi            #+#    #+#             */
/*   Updated: 2023/10/31 17:12:45 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*execute_cmds(t_cmd **tavern, t_env **envr, char *pwd)
{
	int		pipfd[2];
	pid_t	pid1;
	t_cmd	*current;
	int		status;
	int		for_next;

	pid1 = -1;
	for_next = 0;
	status = 0;
	current = *tavern;
	if ((*tavern)->next == NULL)
	{
		if (if_builting(&current, envr, &pwd))
				;
		else
		{
			pid1 = fork();
			if (pid1 == 0)
				single_cmd_exec(current, envr);
		}
	}
	else
	{
		while (current)
		{
			if (current->next && pipe(pipfd) == -1)
			{
				error_out("pipe", 0);
				g_status = 1;
			}
			pid1 = fork();
			if (pid1 == 0)
			{
				if (current->next)
				{
					if (dup2(pipfd[1], STDOUT_FILENO) < 0)
					{
						puts("error");
						error_out("dup2 ", 0);
						exit(1);
					}
					close(pipfd[1]);
					close(pipfd[0]);
				}
				if (for_next)
				{
					if (dup2(for_next, STDIN_FILENO) < 0)
					{
						error_out("dup2", 0);
						exit(1);
					}
					close(for_next);
				}
				if (if_builting(&current, envr, &pwd))
					exit(0);
				execute_command(current, envr);
			}
			if (for_next)
				close(for_next);
			if (current->next)
			{
				close(pipfd[1]);
				for_next = pipfd[0];
			}
			current = current->next;
		}
	}
	while(wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	return (pwd);
}

int	if_builting(t_cmd **tavern, t_env **env, char **pwd)
{
	if ((*tavern)->cmd[0] == NULL)
		return (1);
	if (ft_strncmp((*tavern)->cmd[0], "echo", 5) == 0)
		return (echo_builted((*tavern)), 1);
	if (ft_strncmp((*tavern)->cmd[0], "cd", 3) == 0)
		return (cd_builted(tavern, env, pwd), 1);
	else if (ft_strncmp((*tavern)->cmd[0], "pwd", 4) == 0)
		return (print_working_directory(tavern, pwd), 1);
	else if (ft_strncmp((*tavern)->cmd[0], "export", 8) == 0)
		return (ft_export((*tavern), env), 1);
	else if (ft_strncmp((*tavern)->cmd[0], "unset", 7) == 0)
		return (ft_unset((*tavern), env), 1);
	else if (ft_strncmp((*tavern)->cmd[0], "env", 4) == 0)
		return (ft_env(tavern, env, 0), 1);
	else if (ft_strncmp((*tavern)->cmd[0], "exit", 6) == 0)
		return (ft_exit((*tavern)), 1);
	else if (ft_strncmp((*tavern)->cmd[0], "$?", 3) == 0)
		return (ft_putnbr_fd(g_status, 2), 1);

	return (0);
}

void	execute_command(t_cmd *tavern, t_env **envr)
{
	char	**path;
	char	**u_env;
	int		ret;
	int		i;

	u_env = update_env(envr);
	check_redirections(tavern);
	if (ft_strncmp(tavern->cmd[0], "/", 1) == 0 && access(tavern->cmd[0], F_OK) == 0)
	{
		ret = execve(tavern->cmd[0], tavern->cmd, u_env);
		if (ret == -1)
		{
			ft_putstr_fd(tavern->cmd[0], 2);
			write(2, ": command not found\n", 20);
			exit(127);
		}
	}
	else
	{
		path = find_path(u_env);
		if (path == NULL)
		{
			ft_putstr_fd(tavern->cmd[0], 2);
			write(2, ": command not found\n", 20);
			exit(127);
		}
		i = -1;
		while (path[++i])
			path[i] = ft_strjoin_b(path[i], tavern->cmd[0], 1);
		i = command_search(path);
		if (i == -1)
			path[++i] = '\0';
		ret = path_backslash(tavern->cmd[0]);
		if (ret == -1)
		{
			write(2, "minishell: ", 11);
			ft_putstr_fd(tavern->cmd[0], 2);
			write(2, ": No such file or directory\n", 29);
			exit(127);
		}
		ret = execve(path[i], tavern->cmd, u_env);
		if (ret == -1)
		{
			ft_putstr_fd(tavern->cmd[0], 2);
			write(2, ": command not found\n", 20);
			exit(127);
		}
	}
}

void	single_cmd_exec(t_cmd *tavern, t_env **envr)
{
	char	**path;
	int		ret;
	int		i;
	char	**u_env;

	u_env = update_env(envr);
	ret = 0;
	check_redirections(tavern);
	if (ft_strncmp(tavern->cmd[0], "/", 1) == 0 && access(tavern->cmd[0], F_OK) == 0)
	{
		ret = execve(tavern->cmd[0], tavern->cmd, u_env);
		if (ret == -1)
		{
			ft_putstr_fd(tavern->cmd[0], 2);
			write(2, ": command not found\n", 20);
			exit(127);
		}
		return ;
	}
	else
	{
		path = find_path(u_env);
		if (path == NULL)
		{
			ft_putstr_fd(tavern->cmd[0], 2);
			write(2, ": command not found\n", 20);
			exit(127);
		}
		i = -1;
		while (path && path[++i])
			path[i] = ft_strjoin_b(path[i], tavern->cmd[0], 1);
		i = command_search(path);
		if (i == -1)
			path[++i] = '\0';
		ret = path_backslash(tavern->cmd[0]);
		if (ret == -1)
		{
			write(2, "minishell: ", 11);
			ft_putstr_fd(tavern->cmd[0], 2);
			write(2, ": No such file or directory\n", 29);
			exit(127);
		}
		ret = execve(path[i], tavern->cmd, u_env);
		if (ret == -1)
		{
			ft_putstr_fd(tavern->cmd[0], 2);
			write(2, ": command not found\n", 20);
			exit(127);
		}
	}
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

// handle when executing minishell inside minishell, the shell level must be incremented in the env, and will only exit from the main minishell if it reaches the smallest amount; --DONE--

// when exporting a variable without a value (which means without '=' sign), it should not be added in the env, but it will be available when executing export; --DONE--

// handle when the PATH is unseted; the result should be fixed; --DONE--

// error_out must write the msg in the fd_error. --DONE--

// sort the envirement when you print it with export only; --DONE--

// after sorting the export, there is a problem in unsetting it members. --DONE--

// close fd, when piping; --DONE--

// exit status; --DONE--

// 7- --DONE--
// minishell$ $USER
// Schatten: command not found "expected"
// execve: Bad address "result"

// 2- --DONE--
// minishell$ cat -e < a
// $ 	fd_in: No such file or directory  ==> minishell: a: No such file or directory
// $ 	dup2: Bad file descriptor

// minishell$ cat < a >> aa
// $ 	fd_in: No such file or directory  ==> minishell: a: No such file or directory
// $ 	dup2: Bad file descriptor


/***************************************************************************************************************************************************************************************************/


// 1- set the garbage collector;


// 2- change the path when going to the school;




// minishell$ cat << "$USER"
// out > $USER, not the expanded value of $USER;
// same thing for single quotes '$USER';
// no quotes $USER, it should be expanded, $USER VALUE out;



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
