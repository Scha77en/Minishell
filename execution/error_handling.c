/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:45:06 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/28 12:29:46 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../parcing/msh.h"

void	error_out(char *msg, int v)
{
	printf("error_out: %s\n", msg);
	if (v == 0)
		perror(msg);
	if (v == 1)
		write(2, msg, ft_strlen(msg));
	// exit(EXIT_FAILURE);
}
