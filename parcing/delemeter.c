/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delemeter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:47:28 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/10 15:39:49 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int delemeter(char *b, int i, int o_type)
{
	if (i >= 2)
	{
		while (i && (token(b[i - 1], b[i]) != PIPE))
		{
			if (token(b[i - 1], b[i]) == HEREDOC)
				return (DEL);
			i--;
		}
		return (o_type);
	}
	return (o_type);
}

int len_of_delemeter(char *b, int s, int c, int a)
{
    while(b[s] && !is_token_(b[s], c))
    {
        if (b[s] != c)
	    {
	    	s++;
	    	a++;
	    }
        else
            s++;
    }
    return (a);
}
char *fill__delemeter(char *b, int s, int a, int *i)
{
    char *filled;

	filled = my_malloc((a + 1), 1, 1);
	if (!filled)
		return (NULL);
	filled[a] = '\0';
	a = 0;
	while(b[s] && !is_token_(b[s], 34))
	{
       if (b[s] != 34 && b[s] != 39)
			filled[a++] = b[s++];
		else
			s++; 
    }
	if (b[s] == 34 || b[s] == 39)
    	s++;
	*i = s;
	if (!filled)
		return (NULL);
	return (filled);
}
char *fill_delemeter(char *b,  int *i, int c)
{
	char	*f;
	int		a;
	int		s;
	a = 0;
	s = (*i);
	if (cheak(b, i, c) == 1)
	{
		printf("minishell$: syntax error near unexpected token '%c'\n", b[(*i)]);
		return (NULL);
	}
	if (c != 0)
		s++;
	a = len_of_delemeter(b, s, c, a);
	f = fill__delemeter(b, s, a, i);
	return (f);
}
