/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 03:10:54 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/28 03:22:56 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(t_cmd *tavern, t_env **env)
{
	int		i;
	char	**split;

	i = 1;
	if (tavern->cmd[i] == NULL)
		ft_env(env, 1);
	else
	{
		while (tavern->cmd[i] != NULL)
		{
			split = ft_split(tavern->cmd[i], '=');
			// if(plus_sign(split[0]))
			// 	ft_add_value(env, split);
			if (split[1] == NULL)
				ft_add_env(env, split[0], "");
			else
				ft_add_env(env, split[0], split[1]);
			i++;
		}
	}
}

void	ft_add_env(t_env **env, char *var, char *value)
{
	t_env	*current;
	t_env	*new;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->var, var) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new = malloc(sizeof(t_env));
	new->var = ft_strdup(var);
	new->value = ft_strdup(value);
	new->next = NULL;
	ft_lstaddback(env, new);
}
