/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:19:02 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/30 13:19:58 by abouregb         ###   ########.fr       */
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

char	*get_data_r(t_tokens **file)
{
	int		i;
	char	*line;
	char	*data;
	char	*var;
	int		l;

	data = malloc(1);
	if (!data)
		return (NULL);
	data[0] = '\0';
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (!ft_strlen(line))
			break ;
		i = find_exp(line);
		if (i > 0)
		{
			l = i -1;
			var = check_if_valid_herdoc(line, &i);
			if (ft_strlen(var))
				line = update_line(line, var, l);
		}
		if (ft_strncmp(line, ft_strjoin((*file)->tokens, "\n"), ft_strlen(line)) == 0)
			break ;
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
		(*tmp)->fd_out = open((*t_lst)->tokens, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		(*tmp)->fd_out = open((*t_lst)->tokens, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if ((*tmp)->fd_out == -1)
		perror("fd_out");
}

void	rederections(t_tokens **list, t_cmd *tmp)
{
	t_tokens	*t_lst;
	char		*word;
	char		*data;
	t_tokens	*current;

	t_lst = *list;
	current = t_lst;
	if (t_lst->type == IN || t_lst->type == HEREDOC)
	{
		t_lst = t_lst->next;
		if (t_lst->type == WHITESPACE)
			t_lst = t_lst->next;
		word = t_lst->tokens;
		while (is_word(t_lst->next->type))
		{
			word = ft_strjoin(t_lst->tokens, t_lst->next->tokens);
			t_lst = t_lst->next;
		}
		t_lst->tokens = word;
		if (current->type == IN)
			tmp->fd_in = open(t_lst->tokens, O_RDONLY);
		else
		{
			data = get_data_r(&t_lst);
			if (is_word(t_lst->type) && is_word(t_lst->next->type))
				t_lst = t_lst->next;
			tmp->fd_in = writing_data(data);
		}
		if (tmp->fd_in == -1)
			perror("fd_in");
	}
	if (t_lst->type == OUT || t_lst->type == APPEND)
	{
		rederect_o_a(&t_lst, &tmp, current);
	}
	*list = t_lst;
}
