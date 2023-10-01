/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 06:55:04 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/28 20:15:05 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_working_directory(t_cmd *tavern)
{
	char	current_directory[PATH_MAX];

	if (getcwd(current_directory, sizeof(current_directory)) != NULL)
	{
		write(tavern->fd_out, current_directory, ft_strlen(current_directory));
	}
	else
		error_out("getcwd", 0);
	write(tavern->fd_out, "\n", 1);
}
