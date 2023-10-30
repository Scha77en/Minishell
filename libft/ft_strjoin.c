/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:17:33 by abouregb          #+#    #+#             */
/*   Updated: 2022/11/17 13:28:51 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = (char *)my_malloc((ft_strlen(s1) + ft_strlen(s2) + 1), 1, 1);
	if (!str)
		return (NULL);
	while (i <= ft_strlen(s1) && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2) && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
