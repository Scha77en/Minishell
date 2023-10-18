/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:55:29 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/12 19:43:38 by abouregb         ###   ########.fr       */
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
int len_word(char *b, int *i, char **var)
{
	int l;

	l = 0;
	while (b[(*i)] && b[(*i)] != '>' && b[(*i)] != '<' && b[(*i)] != 39
		&& b[(*i)] != '|' && b[(*i)] != 34 && !white_space(b[(*i)]))
	{
		if (b[(*i)] == '$')
		{
			*var = check_if_valid(b, i);
			if (*var != NULL)
				l += ft_strlen(*var);
		}
		else
			l++;
		(*i)++;
	}
	return (l);
}
char *fill_wrd(char *var, int s, char *b, int l)
{
	char	*f;
	int		k;

	k  = 0;
	f = malloc(sizeof(char) * l +1);
	if (!f)
		return (NULL);
	f[l] = '\0';
	while (l)
	{
		if (b[s] == '$' && var != NULL)
		{
			fill_expand(f, &k, var);
			s++;
			l -= ft_strlen(var);
		}
		else if (b[s] == '$' && var == NULL)
			return (free(f), NULL);
		if (l)
		{
			f[k++] = b[s++];
			l--;
		}
	}
	return (f);
}

char	*fill_word(char *b, int *i)
{
	char	*f;
	char	*var;
	int		l;
	int		s;

	var = NULL;
	s = (*i);
	l = len_word(b, i, &var);
	f = fill_wrd(var, s, b, l);
	return (f);
}
