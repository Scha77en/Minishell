/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 03:12:37 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/26 04:03:26 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_cmd *tavern)
{
	int	i;

	i = 0;
	if (tavern->cmd[1] == NULL)
		exit(0);
	else if (tavern->cmd[1] != NULL && tavern->cmd[2] == NULL)
	{
		while (tavern->cmd[1][i] != '\0')
		{
			if (ft_isdigit(tavern->cmd[1][i]) == 0)
			{
				printf("Minishell: exit: %s: numeric argument required\n",
					tavern->cmd[1]);
				exit(255);
			}
			i++;
		}
		exit(ft_atoi(tavern->cmd[1]));
	}
	else
	{
		printf("Minishell: exit: too many arguments\n");
		exit(1);
	}
}
