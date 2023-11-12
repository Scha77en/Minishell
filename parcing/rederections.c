/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:19:02 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/12 19:26:36 by aouhbi           ###   ########.fr       */
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
		signal(SIGINT, herdoc_sigint);
		while (1)
		{
			i = 0;
			line = readline("> ");
			if (!line)
				exit(0);
			if (ft_strlen(line) && ft_strncmp(line, ft_strjoin((*file)->tokens, "\n"), ft_strlen(line)) == 0)
				break ;
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
	printf("pipefd[0]=%d\n", pipfd[0]);
	signal(SIGINT, handle_sigint);
	return (data);
}

int	rederect_o_a(t_tokens **t_lst, t_cmd **tmp, t_tokens *current)
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
	{
		printf("minishell: %s: No such file or directory\n", (*t_lst)->tokens);
		(*tmp)->fd->out = 1;
		while ((*t_lst)->next->type != PIPE && (*t_lst)->next->type != NLINE)
			(*t_lst) = (*t_lst)->next;
		(*tmp)->cmd [0]= NULL;
		g_status = 1;
		return 0;
	}
	return (1);
}

int rederect_in_her(t_tokens **t_lst, t_cmd **tmp, t_tokens *current, t_env **envr)
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
		data = get_data_r(tmp, &(*t_lst), envr);
		if (g_status == 130)
			return (0);
		if (is_word((*t_lst)->type) && is_word((*t_lst)->next->type))
			(*t_lst) = (*t_lst)->next;
	}
	if ((*tmp)->fd->in == -1)
	{
		printf("minishell: %s: No such file or directory\n", (*t_lst)->tokens);
		(*tmp)->fd->in = 0;
		while ((*t_lst)->next->type != PIPE && (*t_lst)->next->type != NLINE)
			(*t_lst) = (*t_lst)->next;
		(*tmp)->cmd[0] = NULL;
		g_status = 1;
		return 0;
	}
	return (1);
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
