/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:12:15 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/13 16:08:28 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens	*create_node(void)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
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
char *t_oken(char *str, int *i, char *b, int type)
{
	int r;

	r = *i;
	while (white_space(b[r+1]))
			r++;
	r++;
	if (type == HEREDOC || type == APPEND)
		r++;
	*i = r;
	return (ft_strdup(str));
}
t_tokens *fill_node(t_tokens *node, char *b, int *i)
{
	if ((node->type = token(b[*i], ' ')) == WHITESPACE)
		node->tokens = t_oken(" ", i, b, -1);
	else if ((node->type = token(b[*i], b[*i + 1])) == PIPE)
		node->tokens = t_oken("|", i, b, -1);
	else if ((node->type = token(b[*i], b[*i + 1])) == HEREDOC)
		node->tokens = t_oken("<<", i, b, HEREDOC);
	else if ((node->type = token(b[*i], b[*i + 1])) == APPEND)
		node->tokens = t_oken(">>", i, b, APPEND);
	else if ((node->type = token(b[*i], b[*i + 1])) == OUT)
		node->tokens = t_oken(">", i, b, -1);
	else if ((node->type = token(b[*i], b[*i + 1])) == IN)
		node->tokens = t_oken("<", i, b, -1);
	else if ((node->type = token(b[*i], b[*i + 1])) == SQUAT)
	{
		if ((node->tokens = fill_token(b, i, 34)) == NULL)
			return (NULL);
	}
	else if ((node->type = token(b[*i], b[*i + 1])) == DQOUT)
	{
		if ((node->tokens = fill_token(b, i, 39)) == NULL)
			return (NULL); 
	}
	else
		node->tokens = fill_word(b, i);
	return (node);
}

t_tokens	*tokenizer(char *b)
{
	int			i;
	t_tokens	*list;
	t_tokens	*node;
	t_tokens	*c_node;

	i = 0;
	list = NULL;
	while (b[i])
	{
		node = create_node();
		c_node =  fill_node(node, b, &i);
		if (!c_node)
			return (NULL);
		add_node(&list, c_node);
	}
	node = create_node();
	node->type = NLINE;
	add_node(&list, node);
	return (list);
}
