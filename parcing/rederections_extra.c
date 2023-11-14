/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:37:23 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/14 08:00:21 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc_process(char **data, int pipfd[2], t_tokens *file, t_env *envr)
{
	int		i;
	char	*line;

	while (1)
	{
		i = 0;
		line = readline("> ");
		if (!line)
		{
			writing_data(*data, pipfd);
			exit(0);
		}
		if (ft_strncmp(line, ft_strjoin(file->tokens, "\n"), 
				ft_strlen(file->tokens)) == 0)
		{
			if ((ft_strlen(file->tokens) >= (ft_strlen(line))))
				break ;
		}
		if (file->type == WORD && (ft_strncmp(line, "\n", ft_strlen(line) + 1))
			&& ft_strlen(line))
			line = fill_word(line, &i, 0, &envr);
		*data = ft_strjoin(*data, ft_strjoin(line, "\n"));
		if (line)
			free(line);
	}
}

void	waiting_herdoc_child(t_cmd **tmp, int pipfd[2])
{
	int		status;

	status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	close(pipfd[1]);
	(*tmp)->fd->in = pipfd[0];
	signal(SIGINT, handle_sigint);
}
