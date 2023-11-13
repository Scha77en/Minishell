/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:31:02 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/13 15:44:54 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = my_malloc((ft_strlen(s1) + 1), 1, 1);
	if (!str)
		return (NULL);
	while (i < (ft_strlen(s1)))
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
