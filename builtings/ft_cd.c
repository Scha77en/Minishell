/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:21:09 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/25 10:18:11 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_cmd *tavern, t_env *env)
{
	if (tavern->cmd[1] == NULL)
	{
		oldpwd_update(env);
		if (chdir(ft_getenv(env, "HOME")) != 0)
			error_out("chdir", 0);
	}
	else if (ft_strcmp(tavern->cmd[1], "-") == 0)
	{
		if (chdir(ft_getenv(env, "OLDPWD")) != 0)
			error_out("chdir", 0);
	}
	else
	{
		oldpwd_update(env);
		if (chdir(tavern->cmd[1]) != 0)
		{
			error_out("chdir", 0);
			return ;
		}
	}
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

char	*ft_getenv(t_env *env, char *var)
{
	t_env	*current;
	size_t	size;
	size_t	i;

	current = env;
	size = ft_strlen(var);
	while (current)
	{
		i = 0;
		while (current->var[i] && current->var[i] != '=')
			i++;
		if (ft_strncmp(current->var, var, size) == 0 && i == size)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
