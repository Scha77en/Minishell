/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:45:33 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/11 19:04:16 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int len_of_filled(char *b, int s, int c, t_env **envr)
{
	int a;

	a = 0;
	while(b[s] && !is_token_(b[s], c))
	{
		if (b[s] == '$' && (b[s+1] == '?'
		|| (b[s+1] && (ft_isdigit(b[s+1]) || !ft_isalnum(b[s+1])))))
			status(b, &s, &a, c);
		else if (b[s] == '$' && c != 39 && b[s+1])
			expand(b, &s, &a, envr);
		else if (b[s] != c)
		{
			s++;
			a++;
		}
		else
			s++;
		if ((b[s] == ' ' || b[s-1] == ' ') && c == 0)
			break ;
	}
	return (a);
}


void fill_exit_s(char **filled, int *s, int *a, char *b)
{
	int i;

	i = 0;
	if (!ft_isalnum(b[(*s) +1]) && b[(*s) + 1] != '?')
	{
		(*filled)[(*a)++] = b[(*s)++];
		return ;
	}
	else if (ft_isdigit(b[(*s) +1]))
	{
		*s += 2;
		return ;
	}
	while(ft_itoa(g_status)[i])
		(*filled)[(*a)++] = ft_itoa(g_status)[i++];
	*s += 2;
}

void fill_expan(char *b,t_index *x, t_env **envr, char **filled)
{
	char *var;
	int n;
	int i;
	n = x->s;
	i = 0;
	var = NULL;
	while (b[n +1] && (ft_isalpha(b[n +1]) || b[n +1] == '_'))
		n++;
	var = fill_var(b, n, x->s);
	x->s += ft_strlen(var) + 1;
	if (ft_getenv(envr, var))
	{
		var = ft_getenv(envr, var);
		while(var[i])
			(*filled)[x->a++] = var[i++];
	}
	else if (!b[x->s] && !(*filled)[0])
		(*filled) = NULL;
}
char *ft_filled(char *b, int *i, int c, char *filled)
{
	if (b[*i] == c && c != 0)
		(*i)++;
	if (!filled)
		return (NULL);
	return (filled);
}

char	*fill_word(char *b, int *i, int c, t_env **envr)
{
	char	*filled;
	t_index x;

	if ((x.s = cheak(b, i, c)) == -1)
		return (NULL);
	x.a = len_of_filled(b, x.s, c, envr);
	filled = my_malloc((x.a + 1), 1, 1);
	if (!filled || (x.a = 0))
		return (NULL);
	filled[x.a] = '\0';
	while(b[x.s] && !is_token_(b[x.s], c) && !(b[x.s] == ' ' && c == 0))
	{
		if (b[x.s] == '$' && b[x.s+1] == '?'  && c != 39 && b[x.s+1])
			fill_exit_s(&filled, &x.s, &x.a, b);
		else if ( b[x.s] == '$' && (ft_isdigit(b[x.s+1]) || !ft_isalnum(b[x.s+1])))
			fill_exit_s(&filled, &x.s, &x.a, b);
		else if (b[x.s] == '$' && c != 39 && b[x.s+1])
			fill_expan(b, &x, envr, &filled);
		else if (b[x.s] != c)
			filled[x.a++] = b[x.s++];
		else
			x.s++;
	}
	*i = x.s;
	return (ft_filled(b, i, c, filled));
}
