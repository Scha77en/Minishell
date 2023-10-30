/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:12:30 by abouregb          #+#    #+#             */
/*   Updated: 2022/11/16 23:00:30 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	l;

	l = 0;
	if (n <= 0)
		l++;
	while (n)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ptr;
	long	nb;

	len = ft_len(n);
	nb = n;
	ptr = (char *)my_malloc(len + 1, 1, 1);
	if (!ptr)
		return (NULL);
	if (nb == 0)
		ptr[0] = '0';
	ptr[len] = '\0';
	if (nb < 0)
	{
		ptr[0] = '-';
		nb = (nb * -1);
	}
	while (nb > 0)
	{
		ptr[len -1] = (nb % 10) + 48;
		nb = nb / 10;
		len--;
	}
	return (ptr);
}
