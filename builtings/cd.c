/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 04:25:57 by aouhbi            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/21 22:35:46 by aouhbi           ###   ########.fr       */
=======
/*   Updated: 2023/09/19 04:27:12 by aouhbi           ###   ########.fr       */
>>>>>>> c0e2fbdd8ca31728e860155aa2bcb10b06966ecf
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_builted(t_cmd *tavern)
{
<<<<<<< HEAD
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
=======
}
>>>>>>> c0e2fbdd8ca31728e860155aa2bcb10b06966ecf
