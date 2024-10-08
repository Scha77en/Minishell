/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:11:47 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/14 07:22:40 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_export(char *split, int *j)
{
	char	**str;
	char	*s0;
	char	*s1;
	int		i;

	i = 0;
	str = my_malloc(3, sizeof(char *), 1);
	while (split[i] != '\0' && split[i] != '=')
		i++;
	if (split[i] == '=')
		*j = 1;
	s0 = ft_substr(split, 0, i);
	s1 = ft_substr(split, i + 1, ft_strlen(split));
	str[0] = back_slash_parce(s0, 0);
	str[1] = back_slash_parce(s1, 0);
	str[2] = NULL;
	return (str);
}

char	*back_slash_parce(char *str, int flag)
{
	int		i;
	int		v;
	char	*new;

	i = 0;
	v = 0;
	new = my_malloc((slash_size(str) + 1), sizeof(char), 1);
	while (str && str[i] != '\0')
	{
		if (str[i] == 92 && str[i + 1] == 92)
		{
			while (str[i] == 92)
				new[v++] = str[i++];
		}
		else if (str[i] == 92 && str[i + 1] != 92)
			i++;
		else
			new[v++] = str[i++];
	}
	if (flag == 0)
		new[v] = '\0';
	return (new);
}

int	slash_size(char *str)
{
	int	i;
	int	v;

	i = 0;
	v = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 92 && str[i + 1] == 92)
		{
			while (str[i] == 92)
			{
				v++;
				i++;
			}
		}
		else if (str[i] == 92 && str[i + 1] != 92)
			i++;
		else
		{
			v++;
			i++;
		}
	}
	return (v);
}
