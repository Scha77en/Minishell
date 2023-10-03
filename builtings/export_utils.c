/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:11:47 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/30 15:04:44 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_export(char *split)
{
	char	**str;
	char	*s0;
	char	*s1;
	static char	*tmp;
	int		i;

	i = 0;
	str = malloc(3 * sizeof(char *));
	if (!str)
		return (NULL);
	while (split[i] != '\0' && split[i] != '=')
		i++;
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
	new = malloc(slash_size(str) + 1 * sizeof(char));
	if (!new)
		exit(EXIT_FAILURE);
	while(str && str[i] != '\0')
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
		free(str);
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
