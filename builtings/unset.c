/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:38:40 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/25 02:26:57 by aouhbi           ###   ########.fr       */
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

static void	free_node(t_env *envr, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	ft_unset(t_cmd *tavern, t_env *env)
{
	t_env	*current;
	t_env	*prev;
	size_t	size;
	size_t	i;

	current = env;
	while (tavern)
	{
		size = env_size(tavern->cmd[1]);
		while (current)
		{
			i = 0;
			while (current->var[i] && current->var[i] != '=')
				i++;
			if (ft_strncmp(current->var, tavern->cmd[1], size) == 0
				&& i == size)
				free_node(envr, current);
			prev = current;
			current = current->next;
		}
		tavern = tavern->next;
	}
	return (0);
}
