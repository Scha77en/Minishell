/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:19:02 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/23 01:55:25 by abouregb         ###   ########.fr       */
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

char	*get_data_r(t_tokens *file)
{
	char	*line;
	char	*data;

	data = malloc(1);
	data[0] = '\0';
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (ft_strncmp(line, ft_strjoin(file->tokens, "\n"), ft_strlen(line)) == 0)
			break ;
		data = ft_strjoin(data, line);
		free(line);
	}
	return (free(line), data);
}

void rederections(t_tokens **list, t_cmd *tmp)
{
    t_tokens *t_lst;
    char *data;
    t_lst = *list;
    t_tokens *current = t_lst;
    if(t_lst->type == IN || t_lst->type == HEREDOC)
    {
        t_lst = t_lst->next;
        if (t_lst->type == WHITESPACE)
            t_lst = t_lst->next;
        if (current->type == IN)
            tmp->fd_in = open(t_lst->tokens, O_RDONLY);
        else
        {
            data = get_data_r(t_lst);
            tmp->fd_in = writing_data(data);//HERDOC!!!!!!
            
        }
        if (tmp->fd_in == -1)
        {
            perror("Error\n");
        }
    }
    else if (t_lst->type == OUT || t_lst->type == APPEND)
    {
        t_lst = t_lst->next;
        if (t_lst->type == WHITESPACE)
            t_lst = t_lst->next;
        if (current->type == OUT)
            tmp->fd_out = open(t_lst->tokens,O_CREAT | O_WRONLY | O_TRUNC, 0777);
        else
            tmp->fd_out = open(t_lst->tokens, O_CREAT | O_WRONLY | O_APPEND, 0777);
        if (tmp->fd_out == -1)
            perror("fd_out : Permission denied  .\n");
    }
    *list = t_lst;
}
