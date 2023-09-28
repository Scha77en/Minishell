/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:17:03 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/27 02:31:37 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env **env, int v)
{
	t_env	*current;

	current = *env;
	if (v == 0)
	{
		while (current)
		{
			printf("%s=%s\n", current->var, current->value);
			current = current->next;
		}
	}
	else if (v == 1)
	{
		while (current)
		{
			printf("declare -x %s=\"%s\"\n", current->var, current->value);
			current = current->next;
		}
		printf("\n");
	}
}
