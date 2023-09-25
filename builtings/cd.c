/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 04:25:57 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/25 12:25:26 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_builted(t_cmd *tavern, t_env **env)
{
	char	curwd[PATH_MAX];

	if (tavern->cmd[1] == NULL)
	{
		oldpwd_update(env, NULL, 0);
		if (chdir(ft_getenv(env, "HOME")) != 0)
			error_out("chdir", 0);
		pwd_update(env);
	}
	else if (ft_strcmp(tavern->cmd[1], "-") == 0)
	{
		if (getcwd(curwd, PATH_MAX) == NULL)
			error_out("getcwd", 1);
		if (chdir(ft_getenv(env, "OLDPWD")) != 0)
			printf("Minishell: cd: OLDPWD not set\n");
		oldpwd_update(env, curwd, 1);
		pwd_update(env);
	}
	else
	{
		oldpwd_update(env, NULL, 0);
		pwd_update(env);
		if (chdir(tavern->cmd[1]) != 0)
		{
			error_out("chdir", 0);
			return ;
		}
		pwd_update(env);
	}
}

void	oldpwd_update(t_env **env, char *curwd, int v)
{
	char	cwd[PATH_MAX];

	if (v == 0)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
			error_out("getcwd", 0);
		oldpwd_search_update(env, cwd);
	}
	else if (v == 1)
	{
		oldpwd_search_update(env, curwd);
		if (getcwd(curwd, PATH_MAX) == NULL)
			error_out("getcwd", 0);
		printf("%s\n", curwd);
	}
}

void	pwd_update(t_env **env)
{
	char	cwd[PATH_MAX];
	t_env	*current;

	if (getcwd(cwd, PATH_MAX) == NULL)
		error_out("getcwd", 0);
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
}

void	oldpwd_search_update(t_env **env, char *cwd)
{
	t_env	*current;
	t_env	*new;
	int		v;

	printf("oldpwd_search_update\n");
	v = 0;
	current = *env;
	while (current)
	{
		if (ft_strncmp_m(current->var, "OLDPWD", 6) == 0)
		{
			printf("deleting oldpwd\n");
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
				printf("adding oldpwd\n");
				new = ft_envnew(ft_strdup("OLDPWD"));
				new->value = ft_strdup(cwd);
				new->next = current->next;
				current->next = new;
				return ;
			}
			current = current->next;
		}
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

// void	cd_builted(t_cmd *tavern, t_env *env)
// {
// 	oldpwd_update(env);
// 	if (chdir(tavern->cmd[1]) != 0)
// 	{
// 		error_out("chdir", 0);
// 		return (1);
// 	}
// 	return (0);
// }

// void	oldpwd_update(t_env *env)
// {
// 	char	cwd[PATH_MAX];

// 	if (getcwd(cwd, PATH_MAX) == NULL)
// 		error_out("getcwd", 0);
// 	oldpwd_search_update(env, cwd);
// }

// void	oldpwd_search_update(t_env *env, char *cwd)
// {
// 	t_env	*current;
// 	t_env	*new;

// 	current = env;
// 	while (current)
// 	{
// 		if (ft_strncmp(current->var, "OLDPWD=", 7) == 0)
// 		{
// 			ft_memdel(current->value);
// 			current->value = cwd;
// 			return ;
// 		}
// 		current = current->next;
// 	}
// 	current = env;
// 	while (current)
// 	{
// 		if (ft_strncmp(current->var, "PWD=", 4) == 0)
// 		{
// 			new = ft_envnew(ft_strdup("OLDPWD="));
// 			new->value = cwd;
// 			new->next = current->next;
// 			current->next = new;
// 			return ;
// 		}
// 		current = current->next;
// 	}
// }

// t_env	*ft_envnew(char *var)
// {
// 	t_env	*new;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 		return (NULL);
// 	new->var = var;
// 	new->value = NULL;
// 	new->next = NULL;
// 	return (new);
// }

void	ft_memdel(void *ptr)
{
	if (ptr)
	{
		printf("memdel\n");
		free(ptr);
		ptr = NULL;
	}
}
