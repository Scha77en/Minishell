/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:11:44 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/19 18:45:23 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd *create_list(t_fd **fd)
{
	t_cmd *node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->fd = *fd;
	node->cmd = NULL;
	node->next = NULL;
	return (node);
}

t_cmd	*ft_lstlast_p(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}



void add_list(t_cmd **list, t_cmd *new)
{
	t_cmd *tmp;
	tmp = NULL;
	if (!(*list))
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int n_of_cmd(t_tokens *list)
{
	int r;

	r = 0;
	while(list->type != PIPE && list->type != NLINE)
	{
		if(is_word(list->type) && !is_word(list->next->type))
			r++;
		else if (is_word(list->type) && is_word(list->next->type))
		{
			while(is_word(list->next->type))
				list = list->next;
			r++;
		}
		else if (list->type == IN || list->type == OUT || list->type == HEREDOC || list->type == APPEND)
		{
		   list = list->next;
			if (list->type == WHITESPACE)
				list = list->next;
			while(is_word(list->next->type))
				list = list->next;
		}
		list = list->next;
	}
	return (r);
}

void fill(t_tokens **list, t_cmd **tmp, int *i)
{
	char *word;
	char *tmpe;

		if (is_word((*list)->type))
		{
			word = (*list)->tokens;
			while(is_word((*list)->next->type))
			{
				tmpe = ft_strjoin(word, (*list)->next->tokens);
				free(word);
				word = tmpe;
				(*list) = (*list)->next;
			}
			(*tmp)->cmd[++(*i)] = word;
			// free(tmpe);
		}
	if ((*list)->type == IN || (*list)->type == OUT
		|| (*list)->type == HEREDOC || (*list)->type == APPEND)
		rederections(list, tmp);
}
