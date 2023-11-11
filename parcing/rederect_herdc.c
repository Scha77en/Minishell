/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederect_herdc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:26:34 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/11 14:48:33 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void rederect_append(t_cmd **tmp, t_tokens **t_lst)
{
	if ((*tmp)->fd->out != 1)
		close((*tmp)->fd->out);
	(*tmp)->fd->out = open((*t_lst)->tokens, O_CREAT | O_WRONLY | O_APPEND, 0777);
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
		rederect_append(tmp, t_lst);
	if ((*tmp)->fd->out == -1)
		return (print_erorr(tmp, 1, t_lst));
	return (1);
}

void rederect_her( t_cmd **tmp, char **data, t_tokens **t_lst, t_env **envr)
{
	if ((*tmp)->fd->in != 0)
		close((*tmp)->fd->in);
	*data = get_data_r(&(*t_lst), envr);
	if (is_word((*t_lst)->type) && is_word((*t_lst)->next->type))
		(*t_lst) = (*t_lst)->next;
	(*tmp)->fd->in = writing_data(*data);
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
		rederect_her(tmp, &data, t_lst, envr);
	if ((*tmp)->fd->in == -1)
		return(print_erorr(tmp, 0, t_lst));
	return (1);
}
