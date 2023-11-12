/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:22:41 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/12 17:25:39 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cheak(char *b, int *i, int c)
{
	int	s;
	int	r;

	s = *i;
	r = 1;
	while (b[++s])
	{
		if (b[s] == c)
			r = 0;
	}
	if (r == 1 && (c == 34 || c == 39))
	{
		printf("minishell$: syntax error near unexpected token `%c'\n", b[(*i)]);
		return (-1);
	}
	else if (c == 34 || c == 39)
		return ((*i) + 1);
	else
		return (*i);
}

int	token(char fc, char sc)
{
	if (fc == '|')
		return (PIPE); 
	else if (fc == 39)
		return (DQOUT);
	else if (fc == 34)
		return (SQUAT);
	else if (fc == '>' && sc == '>')
		return (APPEND);
	else if (fc == '<' && sc == '<')
		return (HEREDOC);
	else if (fc == '<' && sc != '<')
		return (IN);
	else if (fc == '>' && sc != '>')
		return (OUT);
	else if (fc == ' ')
		return (WHITESPACE);
	else if (fc == 92)
		return (SLH);
	else
		return (WORD);
}

int	is_word(int type)
{
	if (type == WORD || type == SQUAT
		|| type == DQOUT || type == DEL)
		return (1);
	return (0);
}

int	is_token(int type)
{
	if (type == PIPE || type == IN || type == OUT
		|| type == HEREDOC || type == APPEND)
		return (1);
	return (0);
}

int	syntax_error(t_tokens *list)
{
	if (list->type == PIPE)
	{
		g_status = 258;
		printf("minishell$: syntax error near \
		unexpected token '%s'\n", list->tokens);
		return (1);
	}
	while (list)
	{
		if (((is_token(list->type) && !is_word(list->next->type)
					&& list->next->type != WHITESPACE)) || list->type == SLH)
		{
			g_status = 258;
			printf("minishell$: syntax error near \
			unexpected token '%s'\n", list->tokens);
			return (1);
		}
		else
			list = list->next;
	}
	return (0);
}
