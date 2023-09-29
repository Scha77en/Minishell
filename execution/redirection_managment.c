/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_managment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:18:29 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/29 13:41:47 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_redirections(t_cmd *tavern)
{
	if (tavern->fd_in != 0)
	{
		if (dup2(tavern->fd_in, STDIN_FILENO) < 0)
			error_out("dup2", 0);
		close(tavern->fd_in);
	}
	if (tavern->fd_out != 1)
	{
		if (dup2(tavern->fd_out, STDOUT_FILENO) < 0)
			error_out("dup2", 0);
		close(tavern->fd_out);
	}
}