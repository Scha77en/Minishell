/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:46:18 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/26 11:43:57 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	rows_num(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*get_word(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = my_malloc((finish - start + 1), 1, 1);
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split_m(char *s, char c)
{
	size_t	g_end;
	size_t	j;
	int		g_start;
	char	**ptr;

	ptr = my_malloc((rows_num(s, c) + 1), sizeof(char *), 1);
	if (!s || !ptr)
		return (0);
	g_end = -1;
	j = 0;
	g_start = -1;
	while (++g_end <= ft_strlen_m(s))
	{
		if (s[g_end] != c && g_start < 0)
			g_start = g_end;
		else if ((s[g_end] == c || g_end == ft_strlen_m(s)) && g_start >= 0)
		{
			ptr[j++] = get_word(s, g_start, g_end);
			if (!ptr[j - 1])
				return (NULL);
			g_start = -1;
		}
	}
	return (ptr[j] = 0, ptr);
}
