/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:38:40 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/13 17:36:05 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_cmd *tavern, t_env **envr)
{
	int		i;
	t_env	*tmp;
	t_env	*prev;
	char	*target;

	unset_parce(tavern);
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
				erasing_node(envr, tmp, prev);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	unset_parce(t_cmd *tavern)
{
	int		i;
	int		j;

	i = 0;
	while (tavern->cmd[++i])
	{
		j = 0;
		if (tavern->cmd[i][j] == '\0')
			unvalide_identifier(tavern, i);
		else
		{
			while (tavern->cmd[i][j] != '\0')
			{
				if (tavern->cmd[i][j] == ' ' || tavern->cmd[i][j] == '\t')
				{
					unvalide_identifier(tavern, i);
					break ;
				}
				j++;
			}
		}
	}
}

void	erasing_node(t_env **envr, t_env *tmp, t_env *prev)
{
	if (prev == NULL)
		*envr = tmp->next;
	else
		prev->next = tmp->next;
}

void	unvalide_identifier(t_cmd *tavern, int i)
{
	write(2, "minishell: unset: `", 19);
	write(2, tavern->cmd[i], ft_strlen(tavern->cmd[i]));
	write(2, "': not a valid identifier\n", 26);
	g_status = 1;
}
