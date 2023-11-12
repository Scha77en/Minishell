/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:19:02 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/12 17:49:48 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	writing_data(char *data, int fd, int v)
{
	char	*info;

	info = "....";
	if (v == 1)
	{
		write (fd, data, ft_strlen(data));
		close(fd);
		return (0);
	}
	else
	{
		fd = open(info, O_RDONLY, 0777);
		if (fd == -1)
			perror("open");
		if (unlink(info) == -1)
			perror("Error deleting file");
		return (fd);	
	}
}

int	open_fd(void)
{
	int		fd;
	char	*info;

	info = "....";
	fd = open(info, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		perror("open");
	return (fd);
}
char	*get_data_r(t_cmd **tmp, t_tokens **file, t_env **envr)
{
	int		status;
	int		i;
	char	*line;
	char	*data;
	int		fd;
	pid_t	pid;

	fd = open_fd();
	signal(SIGINT, SIG_IGN);
	data = my_malloc(1, 1, 1);
	data[0] = '\0';
	if (!data)
		return (NULL);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, herdoc_sigint);
		while (1)
		{
			i = 0;
			line = readline("> ");
			if (ft_strlen(line) && ft_strncmp(line, ft_strjoin((*file)->tokens, "\n"), ft_strlen(line)) == 0)
				break ;
			if ((*file)->type == WORD && ft_strncmp(line, "\n", ft_strlen(line) + 1) != 0)
				line = fill_word(line, &i, 0, envr);
			data = ft_strjoin(data, ft_strjoin(line, "\n"));
			if (line)
				free(line);
		}
		writing_data(data, fd, 1);
		exit(0);
	}
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	(*tmp)->fd->in = writing_data(data, fd, 0);
	signal(SIGINT, handle_sigint);
	return (data);
}
char	*get_data_r(t_tokens **file, t_env **envr)
{
	char	*data;

	data = my_malloc(1, 1, 1);
	data[0] = '\0';
	if (!data)
		return (NULL);
	signal(SIGINT, handle_sigint);
	return (get_data_(data, file, envr));
}
int print_erorr(t_cmd **tmp, int fd, t_tokens **t_lst)
{
	printf("minishell: %s: No such file or directory\n", (*t_lst)->tokens);
	if (fd == 0)
		(*tmp)->fd->in = 0;
	else
		(*tmp)->fd->out = 1;
	while ((*t_lst)->next->type != PIPE && (*t_lst)->next->type != NLINE)
		(*t_lst) = (*t_lst)->next;
	(*tmp)->cmd[0] = NULL;
	g_status = 1;
	return 0;
}

int	rederections(t_tokens **list, t_cmd **tmp, t_env **envr)
{
	int r;
	t_tokens	*t_lst;
	t_tokens	*current;

	t_lst = *list;
	current = t_lst;
	if ((t_lst->type == IN || t_lst->type == HEREDOC))
		r = rederect_in_her(&t_lst, tmp, current, envr);
	if ((t_lst->type == OUT || t_lst->type == APPEND))
		r = rederect_o_a(&t_lst, tmp, current);
	*list = t_lst->next;
	return (r);
}
