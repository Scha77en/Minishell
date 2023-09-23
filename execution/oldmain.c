/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:10:14 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/21 23:16:39 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../parcing/msh.h"

// int	main(int argc, char **argv, char **env)
// {
// 	t_data	*data;
// 	char	*status;
// 	char	*cmd;
// 	int		pipfd[2];

// 	data = NULL;
// 	status = "exit\n";
// 	char *std_path = _PATH_STDPATH;
// 	printf("stdpath = %s\n", std_path);
// 	while (1)
// 	{
// 		write(1, "Minishell> ", 12);
// 		cmd = get_next_line(0);
// 		type_specifier(&data, cmd);
// 		// printf("%s\n", data.cmd);
// 		// exit(0);
// 		// manage_commands(&data, pipfd, env);
// 		// printf("%s\n", data.cmd);
// 		// parcing_cmd(&cmds);
// 		// excuting_cmd(&cmds);
// 	}
// }

// void	type_specifier(t_data **data, char *cmd)
// {
// 	int		i;
// 	char	**ptr;
// 	t_data	*current;

// 	ptr = ft_split(cmd, ' ');
// 	store_cmd_in_nodes(data, ptr);
// 	current = *data;
// 	while (1)
// 	{
// 		if (current->cmd == NULL)
// 			return ;
// 		printf("[%s -> %d]\n", current->cmd, current->type);
// 	}
// }

// void	store_cmd_in_nodes(t_data **data, char **ptr)
// {
// 	t_data	*n_node;
// 	int		i;

// 	i = 0;
// 	while (ptr[i] != NULL)
// 	{
// 		if (ft_strcmp(ptr[i], "|") != 0 && ft_strcmp(ptr[i], "<") != 0
// 				&& ft_strcmp(ptr[i], ">") != 0 && ft_strcmp(ptr[i], ">>") != 0
// 					&& ft_strcmp(ptr[i], "<<") != 0);
// 		{
// 			n_node = ft_lstnew_m(ptr[i], 0);
// 			ft_lstadd_back_m(data, n_node);
// 			// if (ptr[i + 1][0] == '-')
// 			// {
// 			// 	i++;
// 			// 	ft_strjoin_b(n_node->cmd, ptr[i], 0);
// 			// }
// 		}
// 		if (ft_strcmp(ptr[i], "|") == 0)
// 		{
// 			// while(1);
// 			n_node = ft_lstnew_m(ptr[i], 1);
// 			ft_lstadd_back_m(data, n_node);
// 		}
// 		else if (ft_strcmp(ptr[i], "<") == 0)
// 		{
// 			n_node = ft_lstnew_m(ptr[i], 2);
// 			ft_lstadd_back_m(data, n_node);
// 		}
// 		else if (ft_strcmp(ptr[i], ">") == 0)
// 		{
// 			n_node = ft_lstnew_m(ptr[i], 3);
// 			ft_lstadd_back_m(data, n_node);
// 		}
// 		else if (ft_strcmp(ptr[i], ">>") == 0)
// 		{
// 			n_node = ft_lstnew_m(ptr[i], 4);
// 			ft_lstadd_back_m(data, n_node);
// 		}
// 		else if (ft_strcmp(ptr[i], "<<") == 0)
// 		{
// 			n_node = ft_lstnew_m(ptr[i], 5);
// 			ft_lstadd_back_m(data, n_node);
// 		}
// 		// printf("%s\n", n_node->cmd);
// 		i++;
// 	}
	// t_data *current;
	// current = *data;
	// printf("[%s -> %d]\n", current->cmd, current->type);
	// while (1)
	// {
	// 	if (current->cmd == NULL)
	// 		break ;
	// 	printf("[%s -> %d]\n", current->cmd, current->type);
	// 	current = current->next;
	// }
// 	free_mem(ptr, i);
// }

void	manage_commands(t_data *data, int *pipfd, char **env)
{
	char	*cmds;
	pid_t	pid1;
	pid_t	pid2;
	t_data	*current;

	current = data;
	pid1 = fork();
	if (pid1 == 0)
		manage_first_cmd(current, pipfd, env);
	manage_inbetween_cmd(current, pipfd, env);
	pid2 = fork();
	if (pid2 == 0)
		manage_last_cmd(current, pipfd, env);
	else
	{
		wait(0);
		close(pipfd[1]);
		close(pipfd[0]);
	}
	exit(0);
}

void	manage_first_cmd(t_data *current, int *pipfd, char **env)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;

	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		error_out("dup2", 0);
	close(pipfd[1]);
	cmd = ft_split_m(current->cmd, ' ');
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0]);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve", 0);
}

void	manage_inbetween_cmd(t_data *current, int *pipfd, char **env)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;

	while (current->type != 0)
		current = current->next;
	if (dup2(pipfd[0], STDIN_FILENO) < 0)
		error_out("dup2", 0);
	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		error_out("dup2", 0);
	close(pipfd[1]);
	cmd = ft_split_m(current->cmd, ' ');
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0]);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve", 0);
}

void	manage_last_cmd(t_data *current, int *pipfd, char **env)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;
	int		fd2;

	fd2 = open(argv[j + 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd2 == -1)
		error_out("open", 0);
	close(pipfd[1]);
	if (dup2(pipfd[0], STDIN_FILENO) < 0)
		error_out("dup2", 0);
	close(pipfd[0]);
	if (dup2(fd2, STDOUT_FILENO) < 0)
		error_out("dup2", 0);
	close(fd2);
	cmd = ft_split_m(argv[j], ' ');
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0]);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve", 0);
}

// in manage_commands() u deleted the argc because you dont have any use of it
// but u must do a function to know how many commands you have, only commands. how many pipes
// is there any redirections or not, the input redirection, the append and the output one, plus the here_document.
// simply use a member on the struct called type to give each type of input a unique number identifier.
// for example : 0 = command, 1 = pipe(|), 2 = input(<), 3 = output(>), 4 = append(>>), 5 = here_document(<<);


// To do :

// 1. Handle multiple commands with the pipe;

// 2. Create a function that specifies the type of each input;

// 3. Handle the redirections : 3.1 "<" _ 3.2 ">" _ 3.3 ">>";

// 4. Handle the her_doc "<<";

// 5. Handle the expands "$";

// 6. Handle the expands in the her_doc "$PATH";

// 7. Handle the signals "Ctrl C", "Ctrl D", "Ctrl /";

// 8. Handle the exit status _ watch code vault for help;

/* ----------------------------------------------------------------*/

// There is 3 available option to what can the first input be :

// first : a command with it's flags or without them.

// second : a name of a file followed by the "<" input redirection.

// third : the her_doc "<<".

// Other than that there is no other available option as i know of today.

// The way of solving this clearly is by creating multiple functions to

// handle each one of the options available, and after that

// create a function that checks which way should i take in my code depending

// on the first input.