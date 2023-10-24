/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _fill_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:53:15 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/24 14:18:54 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_token_(char *b, int len, int *i, char c)
{
    char	*value;
    int		n;
	int		lv;
	char	*var;

	var = NULL;
	lv = 0;
    while (b[len] && b[len] != c)
	{
		if (b[len] == '$' && c == 34)
		{
			n = len;
			while (b[n +1] && (ft_isalpha(b[n +1]) || b[n +1] == '_'))
				n++;
			if (n == len)
			{
				len += 2;
				var = ft_itoa(g_status);
			}
			else
			{
				var = fill_var(b, n, len);
				lv = ft_strlen(var);
				len += lv;
			}
			if (!ft_isdigit(var[0]))
			{
				value = getenv(var++);
				var = value;
			}
			if (!ft_strlen(var))
				len++;
		}
		else
			len++;
	}
	return (_fill_token(var, len, lv, i, b, c));
}