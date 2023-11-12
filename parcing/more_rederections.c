/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_rederections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:11:49 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/12 13:08:19 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens	*create_node(void)
{
	t_tokens	*node;

	node = my_malloc(sizeof(t_tokens), 1, 1);
	if (!node)
		return (NULL);
	node->tokens = NULL;
	node->next = NULL;
	return (node);
}

void	add_node(t_tokens **list, t_tokens *new)
{
	t_tokens	*tmp;

	if (!(*list))
	{
		*list = new;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*t_oken(char *str, int *i, char *b, int type)
{
	int	r;

	r = *i;
	while (white_space(b[r + 1]))
		r++;
	r++;
	if (type == HEREDOC || type == APPEND)
		r++;
	while (b[r] == ' ')
		r++;
	if (b[r] == 34 && b[*i] == 34)
		*i = r + 1;
	else
		*i = r;
	return (ft_strdup(str));
}

void	fill_rederections(t_tokens **node, char *b, int *i)
{
	(*node)->type = token(b[*i], b[*i + 1]);
	if ((*node)->type == PIPE)
		(*node)->tokens = t_oken("|", i, b, -1);
	else if ((*node)->type == HEREDOC)
		(*node)->tokens = t_oken("<<", i, b, HEREDOC);
	else if ((*node)->type == APPEND)
		(*node)->tokens = t_oken(">>", i, b, APPEND);
	else if ((*node)->type == OUT)
		(*node)->tokens = t_oken(">", i, b, -1);
	else if ((*node)->type == IN)
		(*node)->tokens = t_oken("<", i, b, -1);
}

int	is_rederections(int type)
{
	if (type == PIPE || type == HEREDOC 
		|| type == APPEND || type == OUT || type == IN)
		return (1);
	return (0);
}
