/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:49:11 by abouregb          #+#    #+#             */
/*   Updated: 2022/11/17 13:52:59 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	if (!src && !dst)
		return (NULL);
	if (src == dst)
		return (dst);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
