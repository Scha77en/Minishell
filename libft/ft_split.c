/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 09:14:38 by abouregb          #+#    #+#             */
/*   Updated: 2022/11/16 23:06:45 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	nwords(char *s, char c)
{
	int	i;
	int	b;

	b = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			b++;
		while (s[i] != c && s[i])
			i++;
	}
	return (b);
}

static int	lenwords(char *s, char c, int i)
{
	int	b;

	b = i;
	while (s[i] != c && s[i])
		i++;
	return (i - b);
}

static char	**ft_setword(char **str, const char *s, int b, char c)
{
	int	i;
	int	j;
	int	a;

	j = 0;
	a = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		a = lenwords((char *)s, c, i);
		if (j < b)
		{
			str[j] = ft_substr(s, i, a);
			if (!str[j])
				return (NULL);
			j++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	str[b] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		b;

	if (!s)
		return (NULL);
	b = nwords((char *)s, c);
	str = (char **)my_malloc((b + 1), 1, 1);
	if (!str)
		return (NULL);
	return (ft_setword(str, s, b, c));
}
