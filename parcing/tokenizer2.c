/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:12:15 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/31 19:27:37 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"





char	*fill_var(char *b, int n, int s)
{
	int		i;
	char	*var;

	i = 0;
	var = my_malloc((n - s), 1, 1);
	if (!var)
		return (NULL);
	var[(n - s)] = '\0';
	n = s +1;
	while (b[n] && (ft_isalpha(b[n]) || b[n] == '_'))
	{
		var[i++] = b[n++];
	}
	return (var);
}



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
	while(b[r] == ' ')
		r++;
	if (b[r] == 34)
		*i = r+1;
	return (ft_strdup(str));
}
t_tokens *fill_node(t_tokens *node, char *b, int *i, t_env **envr)
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
		if ((node->tokens = fill_word(b, i, 34, envr)) == NULL)
			return (NULL);
	}
	else if ((node->type = token(b[*i], b[*i + 1])) == DQOUT)
	{
		if ((node->tokens = fill_word(b, i, 39, envr)) == NULL)
			return (NULL);
	}
	else
		node->tokens = fill_word(b, i, 0, envr);
	return (node);
}

t_tokens	*tokenizer(char *b, t_env **envr)
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
		c_node =  fill_node(node, b, &i, envr);
		if (!c_node)
			return (NULL);
		add_node(&list, c_node);
	}
	node = create_node();
	node->type = NLINE;
	add_node(&list, node);
	return (list);
}
