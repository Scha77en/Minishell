/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:19:02 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/12 17:55:01 by aouhbi           ###   ########.fr       */
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
char	*get_data_(t_cmd **tmp, t_tokens **file, t_env **envr)
{
	int		status;
	int		i;
	char	*line;
	char	*file_;

	i = 0;
	while (1)
	{
		i = 0;
		if (g_status == 130)
			break ;
		line = readline("> ");
		file_ = ft_strjoin((*file)->tokens, "\n");
		if (ft_strlen(line) && !ft_strncmp(line, file_, ft_strlen(file_) - 1))
		{
			if (ft_strlen(file_) >= ft_strlen(line))
				break ;
		}
		if ((*file)->type == WORD && ft_strcmp(line, "\n") != 0)
			line = fill_word(line, &i, 0, envr);
		data = ft_strjoin(data, ft_strjoin(line, "\n"));
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

int	print_erorr(t_cmd **tmp, int fd, t_tokens **t_lst)
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
	return (0);
}

int	rederections(t_tokens **list, t_cmd **tmp, t_env **envr)
{
	int			r;
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
