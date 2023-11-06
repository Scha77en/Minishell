/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:45:25 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/26 11:44:05 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_b(char *s1, char *s2, int v)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	ptr = (char *)my_malloc((ft_strlen_m(s1) + ft_strlen_m(s2) + 2), 1, 1);
	if (!ptr)
		return (0);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	sign_check(&ptr, &i, v);
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	return (ptr[i] = '\0', ptr);
}

void	sign_check(char **ptr, size_t *i, int v)
{
	if (v == 0)
		(*ptr)[(*i)++] = ' ';
	if (v == 1)
		(*ptr)[(*i)++] = '/';
	if (v == 2)
		(*ptr)[(*i)++] = '=';
}

char	*ft_strjoin_m(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	ptr = (char *)my_malloc((ft_strlen_m(s1) + ft_strlen_m(s2) + 1), 1, 1);
	if (!ptr)
		return (0);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlen_m(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
