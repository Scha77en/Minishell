/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:45:06 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/28 12:29:46 by aouhbi           ###   ########.fr       */
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
