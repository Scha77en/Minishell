/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:12:15 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/14 10:53:21 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_var(char *b, int n, int s)
{
	int		i;
	char	*var;

	i = 0;
	var = my_malloc((n - s) + 1, 1, 1);
	if (!var)
		return (NULL);
	n = s +1;
	while (b[n] && (ft_isalpha(b[n]) || b[n] == '_'))
	{
		var[i++] = b[n++];
	}
	var[i] = '\0';
	return (var);
}

void	word_(char *b, int *i, t_env **envr, t_tokens **node)
{
	(*node)->type = delemeter(b, *i, WORD);
	if ((*node)->type == DEL)
	{
		(*node)->tokens = fill_delemeter(b, i, 0);
	}
	else
	{
		(*node)->tokens = fill_word(b, i, 0, envr);
	}
	(*node)->type = WORD;
}

t_tokens	*fill_node(t_tokens *node, char *b, int *i, t_env **envr)
{
	node->type = token(b[*i], b[*i + 1]);
	if (node->type == WHITESPACE)
		node->tokens = t_oken(" ", i, b, -1);
	else if (is_rederections(node->type))
		fill_rederections(&node, b, i);
	else if (node->type == SQUAT)
	{
		node->type = delemeter(b, *i, SQUAT);
		if (node->type == DEL)
			node->tokens = fill_delemeter(b, i, 34);
		else
			node->tokens = fill_word(b, i, 34, envr);
	}
	else if (node->type == DQOUT)
		node->tokens = fill_word(b, i, 39, envr);
	else
		word_(b, i, envr, &node);
	if (node->tokens == NULL)
		return (NULL);
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
		c_node = fill_node(node, b, &i, envr);
		if (g_status == -1)
		{
			while (b[i])
				i++;
		}
		add_node(&list, c_node);
	}
	node = create_node();
	node->type = NLINE;
	add_node(&list, node);
	return (list);
}

int	len_of_filled(char *b, int s, int c, t_env **envr)
{
	int	a;

	a = 0;
	while (b[s] && !is_token_(b[s], c))
	{
		if ((b[s] == '$' && b[s + 1])
			&& (ft_isdigit(b[s + 1]) || !ft_isalnum(b[s + 1])))
			status(b, &s, &a, c);
		else if (b[s] == '$' && c != 39 && b[s + 1])
			expand(b, &s, &a, envr);
		else if (b[s] != c)
		{
			s++;
			a++;
		}
		else
			s++;
		if (s && (b[s] == ' ' || b[s - 1] == ' ') && c == 0)
			break ;
	}
	return (a);
}
