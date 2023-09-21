/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 04:25:57 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/21 22:35:46 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_builted(t_cmd *tavern)
{
	oldpwd_update(tavern);
	if (chdir(tavern->cmd[1] != 0))
		error_out("chdir", 0);
	return (0);
}

void	oldpwd_update(t_cmd *env)
{
	oldpwd_search()
	ft_lstadd_back(&env, env);
}