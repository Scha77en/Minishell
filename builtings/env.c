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

void	ft_env(t_cmd **tavern, t_env **env, int v)
{
	t_env	*current;
	char	*path;

	current = *env;
	if (v == 0)
	{
		path = ft_getenv(env, "PATH");
		if (!path)
		{
			write(2, "minishell: env: No such file or directory\n", 42);
			return ;
		}
		while (current)
		{
			if (current->id == 0)
			{
				ft_putstr_fd(current->var, (*tavern)->fd->out);
				write((*tavern)->fd->out, "=", 1);
				ft_putstr_fd(current->value, (*tavern)->fd->out);
				write((*tavern)->fd->out, "\n", 1);
			}
			current = current->next;
		}
	}
	else if (v == 1)
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
		write((*tavern)->fd->out, "\n", 1);
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

void swap(t_env *a, t_env *b)
{
    char *temp_var = a->var;
    char *temp_value = a->value;
    int temp_id = a->id;

    a->var = b->var;
    a->value = b->value;
    a->id = b->id;

    b->var = temp_var;
    b->value = temp_value;
    b->id = temp_id;
}

char	**update_env(t_env **envr)
{
	char	**current;

	current = env_to_char(envr);
	return (current);
}


char	**env_to_char(t_env **env)
{
	t_env	*current;
	char	**u_env;
	int		i;

	current = *env;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	u_env = my_malloc((i + 1), sizeof(char *), 1);
	current = *env;
	i = 0;
	while (current)
	{
		if (!ft_strncmp(current->var, "SHLVL", 5))
			current->value = ft_itoa(ft_atoi(current->value) + 1);
		u_env[i] = ft_strjoin_b(current->var, current->value, 2);
		current = current->next;
		i++;
	}
	u_env[i] = NULL;
	return (u_env);
}
