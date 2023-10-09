/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 04:25:57 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/29 11:43:07 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_builted(t_cmd **tavern, t_env **env, char **pwd)
{
	char	curwd[PATH_MAX];

	if ((*tavern)->cmd[1] == NULL)
	{
		puts("---------[1]--------");
		oldpwd_update(env, NULL, 0);
		if (chdir(ft_getenv(env, "HOME")) != 0)
			error_out("chdir", 0);
		redefine_pwd(pwd, ft_getenv(env, "HOME"));
		pwd_update(env);
	}
	else if (ft_strcmp((*tavern)->cmd[1], "-") == 0)
	{
		puts("---------[2]--------");
		getcwd(curwd, PATH_MAX);
		if (chdir(ft_getenv(env, "OLDPWD")) != 0)
		{
			if (ft_getenv(env, "OLDPWD") == NULL)
				write((*tavern)->fd_out, "Minishell: cd: OLDPWD not set\n", 31);
			else
			{
				write ((*tavern)->fd_out, "Minishell: cd: ", 15);
				write((*tavern)->fd_out, ft_getenv(env, "OLDPWD") ,ft_strlen(ft_getenv(env, "OLDPWD")));
				write((*tavern)->fd_out, " : No such file or directory\n", 30);
			}
			return ;
		}
		redefine_pwd(pwd, ft_getenv(env, "OLDPWD"));
		oldpwd_update(env, curwd, 1);
		pwd_update(env);
	}
	else
	{
		puts("---------[3]--------");
		oldpwd_update(env, NULL, 0);
		pwd_update(env);
		redefine_pwd(pwd, (*tavern)->cmd[1]);
		if (chdir((*tavern)->cmd[1]) != 0)
		{
			write((*tavern)->fd_out, "cd: error retrieving current directory\n", 40);
			return ;
		}
		if (!getcwd(curwd, PATH_MAX))
		{
			write((*tavern)->fd_out, "cd: error retrieving current directory: ", 41);
			write((*tavern)->fd_out, "getcwd : cannot access parent directories: No such file or directory\n", 70);
		}
	}
}

void	oldpwd_update(t_env **env, char *curwd, int v)
{
	char	cwd[PATH_MAX];

	if (v == 0)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
			return ;
		oldpwd_search_update(env, cwd);
	}
	else if (v == 1)
	{
		oldpwd_search_update(env, curwd);
		if (getcwd(curwd, PATH_MAX) == NULL)
			return ;
		printf("%s\n", curwd);
	}
}

void	pwd_update(t_env **env)
{
	char	cwd[PATH_MAX];
	t_env	*current;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	current = *env;
	while (current)
	{
		if (ft_strncmp_m(current->var, "PWD", 3) == 0)
		{
			current->value = ft_strdup(cwd);
			return ;
		}
		current = current->next;
	}
	ft_add_env_pwd(env, ft_strdup("PWD"), ft_strdup(cwd));
}

void	oldpwd_search_update(t_env **env, char *cwd)
{
	t_env	*current;
	t_env	*new;
	int		v;

	// printf("oldpwd_search_update\n");
	v = 0;
	current = *env;
	while (current)
	{
		if (ft_strncmp_m(current->var, "OLDPWD", 6) == 0)
		{
			// printf("deleting oldpwd\n");
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
			{
				// printf("adding oldpwd\n");
				new = ft_envnew(ft_strdup("OLDPWD"), NULL);
				new->value = ft_strdup(cwd);
				new->next = current->next;
				current->next = new;
				return ;
			}
			current = current->next;
		}
	}
}

t_env	*ft_envnew(char *var, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
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
		if (ft_strcmp(current->var, var) == 0)
		{
			free(current->value);
			if (value == NULL)
				current->value = ft_strdup("");
			else
				current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new = malloc(sizeof(t_env));
	new->var = ft_strdup(var);
	new->var = ft_strdup(var);
	new->value = ft_strdup(value);
	new->next = NULL;
	ft_lstaddback(env, new);
}

void	ft_memdel(void *ptr)
{
	if (ptr)
	{
		// printf("memdel\n");
		free(ptr);
		ptr = NULL;
	}
}
