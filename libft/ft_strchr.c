/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:17:24 by abouregb          #+#    #+#             */
/*   Updated: 2022/11/14 17:43:11 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (i <= ft_strlen(ptr))
	{
		if (ptr[i] == (char)c)
		{
			return (ptr + i);
		}
		i++;
	}
	return (NULL);
}
