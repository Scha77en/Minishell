/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:55:29 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/08 17:58:14 by abouregb         ###   ########.fr       */
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
void expand(char *b, int *s, int *a, t_env **envr)
{
	int n;
	char *var;

	n = *s;
	while (b[n +1] && (ft_isalpha(b[n +1]) || b[n +1] == '_'))
		n++;
	var = fill_var(b, n, *s);
	*s += ft_strlen(var) + 1;
	if (ft_getenv(envr, var))
	{
		var = ft_getenv(envr, var);
		*a += ft_strlen(var);
	}
}
void status(char *b, int *s, int *a, int c)
{
	if (b[(*s)] == '$' && b[(*s)+1] == '?'  && c != 39  && b[(*s)+1])
	{
		*a += ft_strlen(ft_itoa(g_status));
		*s += 2;
	}
	else if ( b[(*s)] == '$' && ft_isdigit(b[(*s)+1]))
		*s += 2;
	else if (!ft_isalnum(b[(*s)+1]))
	{
		*s += 2;
		*a += 2;
	}
}
int len_of_filled(char *b, int s, int c, t_env **envr)
{
	int a;

	a = 0;
	while(b[s] && !is_token_(b[s], c))
	{
		if (b[s] == '$' && (b[s+1] == '?' || ft_isdigit(b[s+1]) || !ft_isalnum(b[s+1])))
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
	if (!ft_isalnum(b[(*s) +1]))
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
	int		a;
	int		s;

	if ((s = cheak(b, i, c)) == -1)
		return (NULL);
	a = len_of_filled(b, s, c, envr);
	filled = my_malloc((a + 1), 1, 1);
	if (!filled || (a = 0))
		return (NULL);
	while(b[s] && !is_token_(b[s], c) && !(b[s] == ' ' && c == 0))
	{
		if (b[s] == '$' && b[s+1] == '?'  && c != 39 && b[s+1])
			fill_exit_s(&filled, &s, &a, b);
		else if ( b[s] == '$' && (ft_isdigit(b[s+1]) || !ft_isalnum(b[s+1])))
			fill_exit_s(&filled, &s, &a, b);
		else if (b[s] == '$' && c != 39 && b[s+1])
			fill_expan(b, &s, envr, &a, &filled);//!5
		else if (b[s] != c)
			filled[a++] = b[s++];
		else 
			s++;
	}
	filled[a] = '\0';
	return (*i = s, ft_filled(b, i, c, filled));
}
