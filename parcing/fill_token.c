/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:12:37 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/18 08:15:52 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*_fill_token(char *var, int len, int lv, int *i, char *b, int c)
{
	int n;
	size_t v;
	char *filed;

	v = 0;
	n = 0;
	if (var != NULL)
		len += (ft_strlen(var) - lv) - (*i +1);
	filed = malloc(sizeof(char ) * len);
	if (!filed)
		return (NULL);
	len = *i + 1;
	while (b[len] && b[len] != c)
	{
		if (b[len] == '$' && var != NULL && c == 34)
		{
			while (v < ft_strlen(var))
				filed[n++] = var[v++];
			len += lv +1;
		}
		else
			filed[n++] = b[len++];
	}
	filed[n] = '\0';
	*i = len+1;
    return (filed);
}


char	*fill_token(char *b, int *i, char c)
{
	char	*filed;
	int		len;

	if (cheak(b, i, c) == 1)
	{
		printf("[%c] :syntax error\n", b[(*i)++]);
		return (NULL);
	}
	len = *i + 1;
	filed = fill_token_(b, len, i, c);
	return (filed);
}

char	*fill_var(char *b, int n, int len)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * (n - len));
	if (!var)
		return (NULL);
	var[(n - len)] = '\0';
	n = len +1;
	while (b[n] && (ft_isalpha(b[n]) || b[n] == '_'))
	{
		var[i++] = b[n++];
	}
	return (var);
}
