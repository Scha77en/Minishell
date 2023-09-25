/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 04:25:57 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/25 02:25:08 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_builted(t_cmd *tavern, t_env *env)
{
	oldpwd_update(tavern);
	if (chdir(tavern->cmd[1] != 0))
	{
		error_out("chdir", 0);
		return (1);
	}
	return (0);
}

void	oldpwd_update(t_env *env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		error_out("getcwd", 0);
	oldpwd_search_update(env, cwd);
}

void	oldpwd_search_update(t_env *env, char *cwd)
{
	t_env	*current;
	t_env	*new;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->var, "OLDPWD=", 7) == 0)
		{
			ft_memdel(current->value);
			current->value = cwd;
			return ;
		}
		current = current->next;
	}
	current = env;
	while (current)
	{
		if (ft_strncmp(current->var, "PWD=", 4) == 0)
		{
			new = ft_envnew(ft_strdup("OLDPWD="));
			new->value = cwd;
			new->next = current->next;
			current->next = new;
			return ;
		}
		current = current->next;
	}
}

t_env	*ft_envnew(char *var)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = var;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

void	ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
