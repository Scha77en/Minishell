/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:55:29 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/31 16:58:21 by abouregb         ###   ########.fr       */
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
	if (q != 0 && c != q)
		return (0);
	if (c == '<' || c == '>'  || c == '|' || c == 34 || c == 39)
		return (1);
	return(0);
}
int len_of_filled(char *b, int s, int c, int a, t_env **envr)
{
	int n;
	char *var;

	n = 0;
	while(b[s] && !is_token_(b[s], c))
	{
		if (b[s] == '$' && b[s+1] == '?'  && c != 39  && b[s+1])
		{
			a += ft_strlen(ft_itoa(g_status));
			s += 2;
		}
		else if (b[s] == '$' && c != 39 && b[s+1])
		{
			n = s;
			while (b[n +1] && (ft_isalpha(b[n +1]) || b[n +1] == '_'))
				n++;
			var = fill_var(b, n, s);
			s += ft_strlen(var) + 1;
			if (ft_getenv(envr, var))
			{
				var = ft_getenv(envr, var);
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
		if ((b[s] == ' ' || b[s-1] == ' ') && c == 0)
			break ;
	}
	return (a);
}
void fill_exit_s(char **filled, int *s, int *a)
{
	int i;

	i = 0;
	while(ft_itoa(g_status)[i])
		(*filled)[(*a)++] = ft_itoa(g_status)[i++];
	*s += 2;
}

void fill_expan(char *b, int *s, t_env **envr, int *a, char **filled)
{
	char *var;
	int n;
		
	n = *s;
	var = NULL;
	while (b[n +1] && (ft_isalpha(b[n +1]) || b[n +1] == '_'))
		n++;
	var = fill_var(b, n, *s);
	*s += ft_strlen(var) + 1;
	if (ft_getenv(envr, var))
	{
		var = ft_getenv(envr, var);
		int i;
		i = 0;
		while(var[i])
			(*filled)[(*a)++] = var[i++];
	}
}

char *fill_it(char *b, int s, int c, int a, int *i, t_env **envr)
{
	char *filled;

	filled = my_malloc((a + 1), 1, 1);
	if (!filled)
		return (NULL);
	filled[a] = '\0';
	a = 0;
	while(b[s] && !is_token_(b[s], c))
	{
		if (b[s] == '$' && b[s+1] == '?'  && c != 39 && b[s+1])
			fill_exit_s(&filled, &s, &a);
		else if (b[s] == '$' && c != 39 && b[s+1])
			fill_expan(b, &s, envr, &a, &filled);
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
	if (!filled[0] && b[0] == '$')
		return (NULL);
	return (filled);
	
}

char	*fill_word(char *b, int *i, int c, t_env **envr)
{
	char	*f;
	int		a;
	int		s;

	a = 0;
	if (cheak(b, i, c) == 1 && (c == 34 || c == 39))
	{
		printf("minishell$: syntax error near unexpected token `%c'\n", b[(*i)++]);
		return (NULL);
	}
	s = (*i);
	if (c == 34 || c == 39)
		s++;
	a = len_of_filled(b, s, c, a, envr);
	f = fill_it(b, s, c, a, i, envr);
	return (f);
}
