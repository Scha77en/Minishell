/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:16:37 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/14 06:08:29 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**find_path(char **env)
{
	int		k;
	char	**path;
	char	**tmp;

	k = get_env_path(env);
	if (k == -1)
		return (NULL);
	tmp = ft_split_m(env[k], '=');
	path = ft_split_m(tmp[1], ':');
	return (path);
}

int	get_env_path(char **env)
{
	char	*path;
	int		i;

	path = "PATH=";
	i = 0;
	while (ft_strncmp_m(path, env[i], 5) != 0)
	{
		if (!env[i])
			return (-1);
		i++;
	}
	return (i);
}

int	ft_strncmp_m(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
