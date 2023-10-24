/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:55:29 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/24 17:03:53 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\f' || c == '\v')
		return (1);
	return (0);
}
int is_token_(int c, int q)
{
	if (c == q)
		return (0);
	if (c == '<' || c == '>' || c == 34 || c == 39)
		return (1);
	return(0);
}
int len_of_filled(char *b, int s, int c, int a)
{
	int n;
	char *var;

	n = 0;
	while(b[s] && !is_token_(b[s], c))
	{
		if (b[s] == '$' && b[s+1] == '?'  && c != 39)
		{
			a += ft_strlen(ft_itoa(g_status));
			s += 2;
		}
		else if (b[s] == '$' && c != 39)
		{
			n = s;
			while (b[n +1] && (ft_isalpha(b[n +1]) || b[n +1] == '_'))
				n++;
			var = fill_var(b, n, s);
			s += ft_strlen(var) + 1;
			if (getenv(var))
			{
				var = getenv(var);
				a += ft_strlen(var);
			}
		}
		else if (b[s] != c)
		{
			s++;
			a++;
		}
		else
			s++;
		if (b[s] == ' ' && c == 0)
			break ;
	}
	return (a);
}
void f_expand(char **filled, char *expand, int *a)
{
	int i;

	i = 0;
	while(expand[i])
		*filled[(*a)++] = expand[i++];
}

char *fill_it(char *b, int s, int c, int a, int *i)
{
	char *filled;
	char *var;
	int n;

	filled = malloc(sizeof(char) * a +1);
	var = NULL;
	if (!filled)
		return (NULL);
	filled[a] = '\0';
	a = 0;
	while(b[s] && !is_token_(b[s], c))
	{
		if (b[s] == '$' && b[s+1] == '?'  && c != 39)
		{
			int i;

			i = 0;
			while(ft_itoa(g_status)[i])
				filled[a++] = ft_itoa(g_status)[i++];
			s += 2;
			// f_expand(&filled, ft_itoa(g_status), &a);
		}
		else if (b[s] == '$' && c != 39)
		{
			n = s;
			while (b[n +1] && (ft_isalpha(b[n +1]) || b[n +1] == '_'))
				n++;
			var = fill_var(b, n, s);
			s += ft_strlen(var) + 1;
			if (getenv(var))
			{
				var = getenv(var);
				int i;

				i = 0;
				while(var[i])
					filled[a++] = var[i++];
				// f_expand(&filled, var, &a);
			}
		}
		else if (b[s] != c)
			filled[a++] = b[s++];
		else
			s++;
		if (b[s] == ' ' && c == 0)
			break ;
	}
	if (b[s] == c && c != 0)
		s++;
	*i = s;
	return (filled);
	
}

char	*fill_word(char *b, int *i, int c)
{
	char	*f;
	int		a;
	int		s;

	a = 0;
	if (cheak(b, i, c) == 1 && (c == 34 || c == 39))
	{
		printf("[%c] :syntax error\n", b[(*i)++]);
		return (NULL);
	}
	s = (*i);
	if (c == 34 || c == 39)
		s++;
	a = len_of_filled(b, s, c, a);
	f = fill_it(b, s, c, a, i);
	return (f);
}
