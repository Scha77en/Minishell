/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:45:06 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/13 17:48:09 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_out(char *msg, int v)
{
	if (v == 0)
		perror(msg);
	if (v == 1)
		write(2, msg, ft_strlen(msg));
}

void	command_not_found(t_cmd *tavern)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(tavern->cmd[0], 2);
	write(2, ": command not found\n", 20);
	exit(127);
}

void	no_such_file(t_cmd *tavern)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(tavern->cmd[0], 2);
	write(2, ": No such file or directory\n", 29);
	exit(127);
}

void	fork_failed(void)
{
	write (2, "minishell: fork: failed to create a child process\n", 50);
	g_status = 1;
}
