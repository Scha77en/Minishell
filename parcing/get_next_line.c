/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:27:02 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/22 07:02:50 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tchek_nl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (1);
	return (0);
}

char	*get_read(int fd, char *s)
{
	char	*b;
	int		nb;

	nb = 1;
	b = (char *)my_malloc((BUFFER_SIZE + 1), sizeof(char), 1);
	while (!tchek_nl(s) && nb > 0)
	{
		nb = read(fd, b, BUFFER_SIZE);
		if ((nb < 0) || (nb == 0 && !s) || (nb == 0 && s[0] == '\0'))
			return (NULL);
		b[nb] = '\0';
		s = ft_strjoin(s, b);
	}
	return (s);
}

char	*getlline(char *s)
{
	char	*l;
	int		i;
	int		a;

	a = 0;
	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (s[i] == '\n')
		l = (char *)my_malloc((i +2), sizeof(char), 1);
	else
		l = (char *)my_malloc((i +1), sizeof(char), 1);
	if (!l)
		return (NULL);
	while (s[a] && a < i +1)
	{
		l[a] = s[a];
		a++;
	}
	l[a] = '\0';
	return (l);
}

char	*get_next(char *s)
{
	int		i;
	char	*c;
	int		a;

	a = 0;
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	c = (char *)my_malloc((ft_strlen(s) - i + 1), 1, 1);
	if (!c)
		return (NULL);
	while (s[i] && a < i)
		c[a++] = s[i++];
	c[a] = '\0';
	return (c);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*l;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	s = get_read(fd, s);
	if (!s)
		return (NULL);
	l = getlline(s);
	s = get_next(s);
	return (l);
}
