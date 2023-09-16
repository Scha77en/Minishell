/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:51:28 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/16 14:01:46 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc_management(t_final_list *final, int *pipfd, char **env)
{
	char	*data;
	int		j;
	pid_t	pid1;
	pid_t	pid2;

	data = get_data(&final);
	pid1 = fork();
	if (pid1 == 0)
		manage_heredoc_first(argv, pipfd, env, data);
	j = command_handler_heredoc(argc, argv, pipfd, env);
	pid2 = fork();
	if (pid2 == 0)
		manage_last_child(argv, pipfd, env, j);
	else
	{
		wait(0);
		close(pipfd[1]);
		close(pipfd[0]);
	}
	exit(0);
}

char	*get_data(t_final_list *final)
{
	char	*line;
	char	*data;

	data = malloc(1);
	data[0] = '\0';
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (ft_strcmp_herdoc(line, argv[2]) == 0)
			break ;
		data = ft_strjoin(data, line);
		free(line);
	}
	return (free(line), data);
}

int	ft_strcmp_herdoc(char *s1, char *s2)
{
	size_t	i;
	int		v;

	v = 0;
	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[0] == '\n')
			v = 1;
		if (s1[i] == '\n' && v == 0)
			break ;
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	manage_heredoc_first(char **argv, int *pipfd, char **env, char *data)
{
	char	**cmd;
	char	**path;
	int		fd;
	int		ret;
	int		i;

	fd = writing_data(data);
	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		error_out("dup2", 0);
	close(pipfd[1]);
	if (dup2(fd, STDIN_FILENO) < 0)
		error_out("dup2", 0);
	close(fd);
	cmd = ft_split(argv[3], ' ');
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0]);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve", 0);
}

int	command_handler_heredoc(int argc, char **argv, int *pipfd, char **env)
{
	int		cmd_n;
	pid_t	pid_b;
	int		j;

	cmd_n = argc - 6;
	j = 4;
	while (cmd_n > 0)
	{
		pid_b = fork();
		if (pid_b == 0)
			manage_children(argv, pipfd, env, j);
		else
			waitpid(pid_b, NULL, 0);
		j++;
		cmd_n--;
	}
	return (j);
}

int	writing_data(char *data)
{
	int		fd;
	char	*info;

	info = generate_file();
	fd = open(info, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		error_out("open", 0);
	write (fd, data, ft_strlen(data));
	close(fd);
	fd = open(info, O_RDONLY, 0777);
	if (fd == -1)
		error_out("open", 0);
	if (unlink(info) == -1)
		perror("Error deleting file");
	return (fd);
}