/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:51:28 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/22 07:05:02 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc_management(t_cmd *tavern, int *pipfd, char **env)
{
	char	*data;
	int		j;
	pid_t	pid1;

	data = get_data_r(tavern);
	pid1 = fork();
	if (pid1 == 0)
		here_doc_cmd(tavern->cmd, pipfd, env, data);
	else
	{
		wait(0);
		close(pipfd[1]);
		close(pipfd[0]);
	}
	exit(0);
}

char	*get_data_hr(t_cmd *tavern)
{
	char	*line;
	char	*data;

	data = malloc(1);
	data[0] = '\0';
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (ft_strcmp_herdoc(line, final->rederections->file) == 0)
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

void	here_doc_cmd(char *cmd, int *pipfd, char **env, char *data)
{
	char	**cmd;
	char	**path;
	int		fd;
	int		ret;
	int		i;

	fd = writing_data(data);
	close(pipfd[1]);
	if (dup2(fd, STDIN_FILENO) < 0)
		error_out("dup2", 0);
	close(fd);
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0], 1);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve", 0);
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

char	*generate_file(void)
{
	int		i;
	int		j;
	char	*info;
	char	*new_name;
	char	*characters;

	characters = "HiddenabcdefghijklmnopqrstuvwxyzABCDE\
				FGHIJKLMNOPQRSTUVWXYZ0123456789";
	j = 0;
	info = ".Hidden";
	while (1)
	{
		i = 1;
		new_name = malloc(ft_strlen(info) + 1);
		new_name[0] = '.';
		while (info[i] != '\0')
		{
			new_name[i++] = characters[j++];
			if (characters[j] == '\0')
				j = 0;
		}
		new_name[i] = '\0';
		if (access(new_name, F_OK) != 0)
			break ;
	}
	return (new_name);
}
