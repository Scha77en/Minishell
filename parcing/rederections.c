/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:19:02 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/13 14:29:31 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	writing_data(char *data, int pipfd[2])
{
	close(pipfd[0]);
	write (pipfd[1], data, ft_strlen(data));
	close(pipfd[1]);
	return (0);
}

char	*get_data_r(t_cmd **tmp, t_tokens **file, t_env **envr)
{
	int		status;
	int		i;
	char	*line;
	char	*data;
	int		pipfd[2];
	pid_t	pid;

	if (pipe(pipfd) == -1)
		return (NULL);
	signal(SIGINT, SIG_IGN);
	data = my_malloc(1, 1, 1);
	data[0] = '\0';
	if (!data)
		return (NULL);
	pid = fork();
	if (pid == 0)
	{
		i = 0;
		if (g_status == 130)
			break ;
		line = readline("> ");
		file_ = ft_strjoin((*file)->tokens, "\n");
		if (!ft_strncmp(line, file_, ft_strlen(file_) - 1))
		{
			i = 0;
			line = readline("> ");
			if (!line)
			{
				writing_data(data, pipfd);
				exit(0);
			}
			if (ft_strncmp(line, ft_strjoin((*file)->tokens, "\n"), ft_strlen((*file)->tokens)) == 0)
			{
				if ((ft_strlen((*file)->tokens) >= (ft_strlen(line))))
					break ;
			}
			if ((*file)->type == WORD && ft_strncmp(line, "\n", ft_strlen(line) + 1) != 0)
				line = fill_word(line, &i, 0, envr);
			data = ft_strjoin(data, ft_strjoin(line, "\n"));
			if (line)
				free(line);
		}
		writing_data(data, pipfd);
		exit(0);
	}
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	close(pipfd[1]);
	(*tmp)->fd->in = pipfd[0];
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
