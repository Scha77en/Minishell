/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:19:07 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/19 15:46:23 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*sp;
	unsigned char	*spp;
	size_t			i;

	i = 0;
	sp = (unsigned char *)s1;
	spp = (unsigned char *)s2;
	while (i < n && (sp[i] || spp[i]))
	{
		if (sp[i] == spp[i])
			i++;
		else
			return (sp[i] - spp[i]);
	}
	return (0);
}
