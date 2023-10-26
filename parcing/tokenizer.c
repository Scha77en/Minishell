/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:22:41 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/25 16:07:58 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cheak(char *b, int *i, int c)
{
	int s;
	int v;
	s = *i;
	v = 0;
	s = 0;
	while (b[s])
	{
		if (b[s++] == c)
			v++;
	}
	return (v % 2);
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
		|| type == DQOUT)
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
	while (list)
	{
		if (((is_token(list->type) && !is_word(list->next->type)
				&& list->next->type != WHITESPACE)) || list->type == SLH)
			return (printf("syntax error : %s\n", list->tokens), 258);
		else
			list = list->next;
	}
	return (0);
}