/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:34:36 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/13 15:44:59 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = ft_strlen(dst);
	if (l > dstsize || !dstsize)
		return (ft_strlen(src) + dstsize);
	if (dstsize == 0)
		return (ft_strlen(src));
	while ((i + l < dstsize - 1) && src[i])
	{
		dst[i + l] = src[i];
		i++;
	}
	dst[i + l] = 0;
	return (l + ft_strlen(src));
}
