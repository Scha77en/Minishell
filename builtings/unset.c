/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:38:40 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/26 04:03:38 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_env *env, t_env *current)
{
	t_env	*prev;

	prev = env;
	while (prev->next != current)
		prev = prev->next;
	prev->next = current->next;
	ft_memdel(current->var);
	ft_memdel(current->value);
	ft_memdel(current);
}

void	ft_unset(t_cmd *tavern, t_env *env)
{
	t_env	*current;
	size_t	size;
	size_t	i;

	current = env;
	size = env_size(tavern->cmd[1]);
	i = 0;
	while (current)
	{
		while (current->var[i] && current->var[i] != '=')
			i++;
		if (ft_strncmp(current->var, tavern->cmd[1], size) == 0
			&& i == size)
		{
			free_node(env, current);
			return ;
		}
		current = current->next;
	}
}
