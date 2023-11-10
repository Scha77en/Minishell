/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:55:29 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/10 18:12:46 by abouregb         ###   ########.fr       */
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

