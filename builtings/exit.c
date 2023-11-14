/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 03:12:37 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/14 16:55:54 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_cmd *tavern)
{
	int	i;

	i = 0;
	if (tavern->cmd[1] == NULL)
	{
		printf("exit\n");
		exit(g_status);
	}
	else if (tavern->cmd[1] != NULL)
	{
		if (tavern->cmd[1][0] == '\0')
			too_much_bro(tavern, 2);
		while (tavern->cmd[1][i] != '\0')
		{
			if (ft_isdigit_exit(tavern) == 0)
			{
				too_much_bro(tavern, 2);
				return ;
			}
			i++;
		}
		exit_choice(tavern);
	}
}

void	exit_choice(t_cmd *tavern)
{
	if (tavern->cmd[2] == NULL)
	{
		if (ft_strlen(tavern->cmd[1]) <= 20)
		{
			check_size(tavern);
			write(2, "exit\n", 5);
			exit(ft_atoi(tavern->cmd[1]));
		}
		else if (ft_strlen(tavern->cmd[1]) > 19)
		{
			too_much_bro(tavern, 2);
		}
	}
	else
		too_much_bro(tavern, 1);
}

void	check_size(t_cmd *tavern)
{
	char	*l_max;
	char	*l_min;

	l_max = "9223372036854775807";
	l_min = "-9223372036854775808";
	if (tavern->cmd[1][0] != '-' && ft_strlen(tavern->cmd[1]) == 19)
	{
		if (ft_strcmp(tavern->cmd[1], l_max) > 0)
			too_much_bro(tavern, 2);
	}
	else if (tavern->cmd[1][0] == '-' && ft_strlen(tavern->cmd[1]) == 20)
	{
		if (ft_strcmp(tavern->cmd[1], l_min) > 0)
			too_much_bro(tavern, 2);
	}
}

void	too_much_bro(t_cmd *tavern, int v)
{
	if (v == 1)
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
		g_status = 1;
	}
	else if (v == 2)
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit: ", 17);
		ft_putstr_fd(tavern->cmd[1], 2);
		write(2, ": numeric argument required\n", 28);
		exit(255);
	}
}

int	ft_isdigit_exit(t_cmd *tavern)
{
	int		i;
	int		v;

	i = 0;
	v = 0;
	while (tavern->cmd[1][i] != '\0')
	{
		if (v == 0 && (tavern->cmd[1][0] == '+' || tavern->cmd[1][0] == '-'))
			v++;
		else if (tavern->cmd[1][i] < 48 || tavern->cmd[1][i] > 57)
			return (0);
		i++;
	}
	return (1);
}
