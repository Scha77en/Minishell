/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:19:02 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/29 17:42:36 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	writing_data(char *data)
{
	int		fd;
	char	*info;

	info = "....";
	fd = open(info, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		perror("open");
	write (fd, data, ft_strlen(data));
	close(fd);
	fd = open(info, O_RDONLY, 0777);
	if (fd == -1)
		perror("open");
	if (unlink(info) == -1)
		perror("Error deleting file");
	return (fd);
}

char	*get_data_r(t_tokens **file, t_env **envr)
{
	int		i;
	char	*line;
	char	*data;

	data = my_malloc(1, 1, 1);
	data[0] = '\0';
	if (!data)
		return (NULL);
	while(1 && signal(SIGINT, handle_sigint) && g_status != 130)
	{
		i = 0;
		// signal(SIGQUIT, SIG_DFL);
		write(1, "herdoc> ", 8);
		line = get_next_line(0);
		if (!ft_strlen(line))
		{
			write(1, "\n", 1);
			break ;
		}
		if ((*file)->type == WORD && ft_strcmp(line, "\n") != 0)
			line = fill_word(line, &i, 0, envr);
		if (ft_strncmp(line, ft_strjoin((*file)->tokens, "\n"), ft_strlen(line)) == 0)
		{
			break ;
		}
		data = ft_strjoin(data, line);
	}
	return (free(line), data);
}
void	rederect_o_a(t_tokens **t_lst, t_cmd **tmp, t_tokens *current)
{
	char	*tp;
	char	*word;

	(*t_lst) = (*t_lst)->next;
	if ((*t_lst)->type == WHITESPACE)
		(*t_lst) = (*t_lst)->next;
	word = (*t_lst)->tokens;
	while (is_word((*t_lst)->next->type))
	{
		tp = ft_strjoin(word, (*t_lst)->next->tokens);
		free(word);
		word = tp;
		(*t_lst) = (*t_lst)->next;
	}
	(*t_lst)->tokens = word;
	if (current->type == OUT)
	{
		if ((*tmp)->fd->out != 1)
			close((*tmp)->fd->out);
		(*tmp)->fd->out = open((*t_lst)->tokens, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	}
	else
	{
		if ((*tmp)->fd->out != 1)
			close((*tmp)->fd->out);
		(*tmp)->fd->out = open((*t_lst)->tokens, O_CREAT | O_WRONLY | O_APPEND, 0777);
	}
	if ((*tmp)->fd->out == -1)
		perror("fd_out");
}

void rederect_in_her(t_tokens **t_lst, t_cmd **tmp, t_tokens *current, t_env **envr)
{
	char		*word;
	char		*data;

	(*t_lst) = (*t_lst)->next;
	if ((*t_lst)->type == WHITESPACE)
		(*t_lst) = (*t_lst)->next;
	word = (*t_lst)->tokens;
	while (is_word((*t_lst)->next->type))
	{
		word = ft_strjoin((*t_lst)->tokens, (*t_lst)->next->tokens);
		(*t_lst) = (*t_lst)->next;
	}
	(*t_lst)->tokens = word;
	if (current->type == IN)
	{
		if ((*tmp)->fd->in != 0)
			close((*tmp)->fd->in);
		(*tmp)->fd->in = open((*t_lst)->tokens, O_RDONLY);
	}
	else
	{
		if ((*tmp)->fd->in != 0)
			close((*tmp)->fd->in);
		data = get_data_r(&(*t_lst), envr);
		if (is_word((*t_lst)->type) && is_word((*t_lst)->next->type))
			(*t_lst) = (*t_lst)->next;
		(*tmp)->fd->in = writing_data(data);
	}
	if ((*tmp)->fd->in == -1)
		perror("fd_in");
}

void	rederections(t_tokens **list, t_cmd **tmp, t_env **envr)
{
	t_tokens	*t_lst;
	t_tokens	*current;

	t_lst = *list;
	current = t_lst;
	if (t_lst->type == IN || t_lst->type == HEREDOC)
		rederect_in_her(&t_lst, tmp, current, envr);
	if (t_lst->type == OUT || t_lst->type == APPEND)
		rederect_o_a(&t_lst, tmp, current);
	*list = t_lst;
}
