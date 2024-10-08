/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 02:21:12 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/12 11:06:14 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_builted(t_cmd *tavern)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (tavern->cmd[i] && tavern->cmd[i][0] == '-' && tavern->cmd[i][1])
	{
		if (ft_strncmp_echo(tavern->cmd[i], "n",
				ft_strlen(tavern->cmd[i])) == 0)
		{
			n = 1;
			i++;
		}
		else
			break ;
	}
	while (tavern->cmd[i] != NULL)
	{
		write(tavern->fd->out, tavern->cmd[i], ft_strlen(tavern->cmd[i]));
		if (tavern->cmd[i + 1] != NULL)
			write(tavern->fd->out, " ", 1);
		i++;
	}
	if (n == 0)
		write(tavern->fd->out, "\n", 1);
}

int	ft_strncmp_echo(char *s1, char *s2, int n)
{
	int	i;
	int	v;

	i = 1;
	v = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (i < n && (s1[i] || s2[v]))
	{
		if (s1[i] != s2[v])
			return (s1[i] - s2[v]);
		i++;
	}
	return (0);
}
