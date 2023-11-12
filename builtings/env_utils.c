/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:08:21 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/12 11:08:41 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**update_env(t_env **envr)
{
	char	**current;

	current = env_to_char(envr);
	return (current);
}

char	**env_to_char(t_env **env)
{
	t_env	*current;
	char	**u_env;
	int		i;

	current = *env;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	u_env = my_malloc((i + 1), sizeof(char *), 1);
	current = *env;
	i = 0;
	while (current)
	{
		if (!ft_strncmp(current->var, "SHLVL", 5))
			current->value = ft_itoa(ft_atoi(current->value) + 1);
		u_env[i] = ft_strjoin_b(current->var, current->value, 2);
		current = current->next;
		i++;
	}
	u_env[i] = NULL;
	return (u_env);
}
