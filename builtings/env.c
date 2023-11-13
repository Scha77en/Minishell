/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:17:03 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/13 13:34:11 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_cmd **tavern, t_env **env, int v)
{
	t_env	*current;

	current = *env;
	if (v == 0)
	{
		while (current)
		{
			if (current->id == 0)
				env_env(tavern, current);
			current = current->next;
		}
	}
	else if (v == 1)
		export_env(tavern, env, current);
}

void	env_env(t_cmd **tavern, t_env *current)
{
	ft_putstr_fd(current->var, (*tavern)->fd->out);
	write((*tavern)->fd->out, "=", 1);
	ft_putstr_fd(current->value, (*tavern)->fd->out);
	write((*tavern)->fd->out, "\n", 1);
}

void	export_env(t_cmd **tavern, t_env **env, t_env *current)
{
	current = copy_env_list(env);
	sort_env(current);
	while (current)
	{
		if (current->id == 0)
		{
			write((*tavern)->fd->out, "declare -x ", 11);
			ft_putstr_fd(current->var, (*tavern)->fd->out);
			write((*tavern)->fd->out, "=\"", 2);
			ft_putstr_fd(current->value, (*tavern)->fd->out);
			write((*tavern)->fd->out, "\"\n", 2);
		}
		else if (current->id == 2)
		{
			write((*tavern)->fd->out, "declare -x ", 11);
			ft_putstr_fd(current->var, (*tavern)->fd->out);
			write((*tavern)->fd->out, "\n", 1);
		}
		current = current->next;
	}
}

void	set_env(t_env **env)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	*env = NULL;
	ft_lstaddback(env, ft_envnew(ft_strdup("PWD"), ft_strdup(cwd)));
	ft_lstaddback(env, ft_envnew(ft_strdup("SHLVL"), ft_strdup("1")));
	ft_lstaddback(env, ft_envnew(ft_strdup("_"), ft_strdup("/usr/bin/env")));
}

void	swap(t_env *a, t_env *b)
{
	char	*temp_var;
	char	*temp_value;
	int		temp_id;

	temp_var = a->var;
	temp_value = a->value;
	temp_id = a->id;
	a->var = b->var;
	a->value = b->value;
	a->id = b->id;
	b->var = temp_var;
	b->value = temp_value;
	b->id = temp_id;
}
