/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:38:40 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/26 23:28:38 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_cmd *tavern, t_env **envr)
{
	int		i;
	t_env	*tmp;
	t_env	*prev;
	char	*target;

	i = 0;
	while (tavern->cmd[++i])
	{
		target = back_slash_parce(tavern->cmd[i], 1);
		tmp = *envr;
		prev = NULL;
		while (tmp)
		{
			if (!ft_strncmp(target, tmp->var, ft_strlen(target) + 1))
			{
				if (prev == NULL)
					*envr = tmp->next;
				else
					prev->next = tmp->next;
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
