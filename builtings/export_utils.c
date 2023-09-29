/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:11:47 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/29 21:57:36 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_export(char *split)
{
	char	**str;
	char	*s0;
	char	*s1;
	char	*tmp;
	int		i;

	i = 0;
	str = malloc(3 * sizeof(char *));
	if (!str)
		return (NULL);
	while (split[i] != '=')
		i++;
	s0 = ft_strndup(split, i);
	s1 = ft_strdup(split + i + 1);
	tmp = back_slash_parce(s0);
	str[0] = tmp;
	s1 = back_slash_parce(s1);
	tmp = back_slash_parce(s1);
	str[1] = tmp;
	free(tmp);
	printf("str[0] = %s\n", str[0]);
	printf("str[1] = %s\n", str[1]);
	str[2] = NULL;
	while(1);
	return (str);
}

char	*back_slash_parce(char *str)
{
	int		i;
	int		v;
	char	*new;

	i = 0;
	v = 0;
	new = malloc (ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	while(str[i] != '\0')
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
	free(str);
	new[v] = '\0';
	return (new);
}
