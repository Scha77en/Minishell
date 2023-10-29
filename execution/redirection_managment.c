/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_managment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:18:29 by aouhbi            #+#    #+#             */
/*   Updated: 2023/10/28 14:14:56 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirections(t_cmd *tavern)
{
	if (tavern->fd->in != 0)
	{
		if (dup2(tavern->fd->in, STDIN_FILENO) < 0)
		{
			error_out("dup2", 0);
			exit(1);
		}
		close(tavern->fd->in);
		return (1);
	}
	if (tavern->fd->out != 1)
	{
		if (dup2(tavern->fd->out, STDOUT_FILENO) < 0)
		{
			error_out("dup2", 0);
			exit(1);
		}
		close(tavern->fd->out);
		return (1);
	}
	return (0);
}