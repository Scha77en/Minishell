/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:17:03 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/27 02:31:37 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env **env, int v)
{
	t_env	*current;

	current = *env;
	if (v == 0)
	{
		while (current)
		{
			if (current->id == 0)
				printf("%s=%s\n", current->var, current->value);
			current = current->next;
		}
	}
	else if (v == 1)
	{
		while (current)
		{
			if (current->id == 0)
				printf("declare -x %s=\"%s\"\n", current->var, current->value);
			else if (current->id == 2)
				printf("declare -x %s\n", current->var);
			current = current->next;
		}
		printf("\n");
	}
}

void	set_env(t_env **env)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	env = NULL;
	ft_lstaddback(env, ft_envnew(ft_strdup("PWD"), cwd));
	ft_lstaddback(env, ft_envnew(ft_strdup("PATH"), ft_strdup("/home/Schatten/.\
	brew/bin:/home/Schatten/.brew/bin:/usr/local/sbin:/\
	usr/local/bin:/usr/sbin:/usr/bin:/sbin:\
	/bin:/usr/local/games:/usr/games")));
	ft_lstaddback(env, ft_envnew(ft_strdup("SHLVL"), ft_strdup("1")));
	ft_lstaddback(env, ft_envnew(ft_strdup("_"), ft_strdup("/usr/bin/env")));
}

void	update_shlvl(t_env **envr, int v)
{
	t_env	*current;

	current = *envr;
	while (current)
	{
		if (ft_strncmp(current->var, "SHLVL", 5) == 0)
		{
			if (v == 1)
				current->value = ft_itoa(ft_atoi(current->value) + 1);
			else if (v == -1)
				current->value = ft_itoa(ft_atoi(current->value) - 1);
			return ;
		}
		current = current->next;
	}
}