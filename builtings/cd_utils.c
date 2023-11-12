/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:04:38 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/12 11:05:08 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	oldpwd_search_update(t_env **env, char *cwd)
{
	t_env	*current;
	int		v;

	v = 0;
	current = *env;
	while (current)
	{
		if (ft_strncmp_m(current->var, "OLDPWD", 6) == 0)
		{
			current->value = ft_strdup(cwd);
			v = 1;
		}
		current = current->next;
	}
	if (v == 0)
	{
		current = *env;
		while (current)
		{
			if (ft_strncmp_m(current->var, "PWD", 3) == 0)
				old_pwd_add(current, cwd);
			current = current->next;
		}
	}
}

void	old_pwd_add(t_env *current, char *cwd)
{
	t_env	*new;

	new = ft_envnew(ft_strdup("OLDPWD"), NULL);
	new->value = ft_strdup(cwd);
	new->next = current->next;
	current->next = new;
	return ;
}

t_env	*ft_envnew(char *var, char *value)
{
	t_env	*new;

	new = my_malloc(sizeof(t_env), 1, 1);
	if (!new)
		return (NULL);
	new->var = var;
	new->value = value;
	new->next = NULL;
	return (new);
}

char	*ft_getenv(t_env **env, char *var)
{
	t_env	*current;
	size_t	size;
	size_t	i;

	current = *env;
	size = ft_strlen(var);
	while (current)
	{
		i = 0;
		while (current->var[i] && current->var[i] != '=')
			i++;
		if (ft_strncmp_m(current->var, var, size) == 0 && i == size)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	ft_add_env_pwd(t_env **env, char *var, char *value)
{
	t_env	*current;
	t_env	*new;

	current = *env;
	while (current)
	{
		if (ft_strncmp(current->var, var, ft_strlen(current->var) + 1) == 0)
		{
			if (value == NULL)
				current->value = ft_strdup("");
			else
				current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new = my_malloc(sizeof(t_env), 1, 1);
	new->var = ft_strdup(var);
	new->value = ft_strdup(value);
	new->next = NULL;
	ft_lstaddback(env, new);
}
