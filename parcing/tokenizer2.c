/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:12:15 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/30 14:53:32 by abouregb         ###   ########.fr       */
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
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_tokens	*tokenizer(char *b, int *exit_status)
{
	int			i;
	t_tokens	*list;
	t_tokens	*node;

	i = 0;
	list = NULL;
	while (b[i])
	{
		node = create_node();
		if ((node->type = token(b[i], ' ')) == WHITESPACE)
		{
			node->tokens = ft_strdup(" ");
			while (white_space(b[i +1]))
				i++;
		}
		else if ((node->type = token(b[i], b[i + 1])) == PIPE)
			node->tokens = ft_strdup("|");
		else if ((node->type = token(b[i], b[i + 1])) == HEREDOC)
		{
			node->tokens = ft_strdup("<<");
			i++;
		}
		else if ((node->type = token(b[i], b[i + 1])) == APPEND)
		{
			node->tokens = ft_strdup(">>");
			i++;
		}
		else if ((node->type = token(b[i], b[i + 1])) == SQUAT)
		{
			if ((node->tokens = fill_token(b, &i, 34, exit_status)) == NULL)
				return (NULL);
		}
		else if ((node->type = token(b[i], b[i + 1])) == DQOUT)
		{
			if ((node->tokens = fill_token(b, &i, 39, exit_status)) == NULL)
				return (NULL); 
		}
		else if ((node->type = token(b[i], b[i + 1])) == OUT)
			node->tokens = ft_strdup(">");
		else if ((node->type = token(b[i], b[i + 1])) == IN)
			node->tokens = ft_strdup("<");
		else
			node->tokens = fill_word(b, &i, exit_status);
		add_node(&list, node);
	}
	node = create_node();
	node->type = NLINE;
	add_node(&list, node);
	return (list);
}

int	syntax_error(t_tokens *list)
{
	while (list)
	{
		if ((is_token(list->type) && !is_word(list->next->type)
				&& list->next->type != WHITESPACE))
			return (printf("syntax error : %s\n", list->tokens), 258);
		else
			list = list->next;
	}
	return (0);
}
