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
	if (tavern->fd->in != 0)
	{
		if (dup2(tavern->fd->in, STDIN_FILENO) < 0)
			error_out("dup2", 0);
		close(tavern->fd->in);
	}
	if (tavern->fd->out != 1)
	{
		if (dup2(tavern->fd->out, STDOUT_FILENO) < 0)
			error_out("dup2", 0);
		close(tavern->fd->out);
	}
}