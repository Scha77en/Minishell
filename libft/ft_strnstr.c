/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:04:56 by abouregb          #+#    #+#             */
/*   Updated: 2022/11/17 13:17:30 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*h;

	h = (char *)haystack;
	i = 0;
	j = 0;
	if (!ft_strlen(needle))
		return (h);
	if (!len)
		return (NULL);
	while (h[i])
	{
		j = 0;
		while (h[i + j] == needle[j] && i < len && j < len - i)
		{
			if (j == (ft_strlen(needle) - 1))
				return (h + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
