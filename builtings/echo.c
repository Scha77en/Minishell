/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 02:21:12 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/26 04:20:53 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_builted(t_cmd *tavern)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (tavern->cmd[i] != NULL && ft_strcmp(tavern->cmd[i], "-n") == 0)
	{
		n = 1;
		i++;
	}
	while (tavern->cmd[i] != NULL)
	{
		printf("%s", tavern->cmd[i]);
		if (tavern->cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
}

void	ft_echo(t_cmd *tavern)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (tavern->cmd[i] != NULL && ft_strcmp(tavern->cmd[i], "-n") == 0)
	{
		n = 1;
		i++;
	}
	while (tavern->cmd[i] != NULL)
	{
		printf("%s", tavern->cmd[i]);
		if (tavern->cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
}