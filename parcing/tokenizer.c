/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:22:41 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/30 00:16:03 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cheak(char *b, int *i, int c)
{
	int s;

	s = *i;
	while (b[++s])
	{
		if (b[s] == c)
			return (0);
	}
	return (1);
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
