/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:00:09 by abouregb          #+#    #+#             */
/*   Updated: 2022/11/12 15:44:23 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	debut(char *s1, char *set)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (set[i])
	{
		while (s1[j] == set[i] && s1[j])
		{
			i = 0;
			j++;
		}
		i++;
	}
	return (j);
}

static int	fin(char *s1, char *set)
{
	int	i;
	int	j;

	j = ft_strlen(s1);
	i = 0;
	while (set[i])
	{
		while (s1[j - 1] == set[i] && s1[j - 1])
		{
			i = 0;
			j--;
			if (j == 0)
				return (0);
		}
		i++;
	}
	return (j);
}

char	*ft_strtrim(char const	*s1, char const	*set)
{
	int		i;
	int		a;
	int		b;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	a = debut((char *)s1, (char *)set);
	b = fin((char *)s1, (char *)set);
	return (ft_substr(s1, a, b - a));
}
