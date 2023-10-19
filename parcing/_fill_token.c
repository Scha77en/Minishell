/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _fill_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:53:15 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/19 17:09:38 by abouregb         ###   ########.fr       */
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
    while (b[len] && b[len] != c)
	{
		if (b[len] == '$' && c == 34)
		{
			n = len;
			while (b[n +1] && (ft_isalpha(b[n +1]) || b[n +1] == '_'))
				n++;
			var = fill_var(b, n, len);
			lv = ft_strlen(var);
			len += lv;
			value = getenv(var++);
			var = value;
			if (!ft_strlen(var))
				len++;
		}
		else
			len++;
	}
	return (_fill_token(var, len, lv, i, b, c));
}

int len_var(char *value, t_env *env)
{
	while(env)
	{
		if (ft_strcmp(value, env->value) == 0)
			return (ft_strlen(env->var) + 1);
		env = env->next;
	}
	return (0);
}