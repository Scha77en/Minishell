/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:38:40 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/13 21:04:19 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_cmd *tavern, t_env **envr)
{
	int		i;
	t_env	*tmp;
	t_env	*prev;
	char	*target;

	i = unset_parce(tavern);
	if (i == 0)
		g_status = 0;
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

int	unset_parce(t_cmd *tavern)
{
	int		i;
	int		j;
	int		v;

	v = 0;
	i = 0;
	while (tavern->cmd[i] != NULL)
	{
		if (!check_validity(tavern->cmd[i], &j))
			v = unvalide_identifier(tavern, i);
		i++;
	}
	i = 0;
	while (tavern->cmd[++i])
	{
		j = 0;
		if (tavern->cmd[i][j] == '\0')
			v = unvalide_identifier(tavern, i);
		else
		{
			while (tavern->cmd[i][j] != '\0')
			{
				if (tavern->cmd[i][j] == ' ' || tavern->cmd[i][j] == '\t')
				{
					v = unvalide_identifier(tavern, i);
					break ;
				}
				j++;
			}
		}
	}
	return (v);
}

void	erasing_node(t_env **envr, t_env *tmp, t_env *prev)
{
	if (prev == NULL)
		*envr = tmp->next;
	else
		prev->next = tmp->next;
}

int	unvalide_identifier(t_cmd *tavern, int i)
{
	write(2, "minishell: unset: `", 19);
	write(2, tavern->cmd[i], ft_strlen(tavern->cmd[i]));
	write(2, "': not a valid identifier\n", 26);
	g_status = 1;
	return (1);
}
