/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:16:37 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/26 11:44:12 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**find_path(char **env)
{
	int		k;
	char	**path;

	k = get_env_path(env);
	path = ft_split_m(env[k], ':');
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
			perror("The Command Path Does Not Exist!");
		i++;
	}
	return (i);
}

int	ft_strncmp_m(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
