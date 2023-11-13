/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 04:25:57 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/13 17:24:10 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_builted(t_cmd **tavern, t_env **env, char **pwd)
{
	char	curwd[PATH_MAX];

	if ((*tavern)->cmd[1] == NULL || ft_strncmp((*tavern)->cmd[1], "--", 3) == 0
		|| ft_strncmp((*tavern)->cmd[1], "~", 2) == 0)
	{
		oldpwd_update(env, NULL, 0);
		if (chdir(ft_getenv(env, "HOME")) != 0)
		{
			error_out("chdir", 0);
			g_status = 1;
			return ;
		}
		redefine_pwd(pwd, ft_getenv(env, "HOME"), env, 0);
		pwd_update(env);
	}
	else if (ft_strncmp((*tavern)->cmd[1], "-",
			ft_strlen((*tavern)->cmd[1]) + 1) == 0)
		cd_dash(tavern, env, pwd, curwd);
	else
		cd_path(tavern, env, pwd, curwd);
}

void	cd_dash(t_cmd **tavern, t_env **env, char **pwd, char *curwd)
{
	getcwd(curwd, PATH_MAX);
	if (chdir(ft_getenv(env, "OLDPWD")) != 0)
	{
		if (ft_getenv(env, "OLDPWD") == NULL)
		{
			write((*tavern)->fd->out, "minishell: cd: OLDPWD not set\n", 30);
			g_status = 1;
		}
		else
		{
			write((*tavern)->fd->out, "minishell: cd: ", 15);
			write((*tavern)->fd->out, ft_getenv(env, "OLDPWD"),
				ft_strlen(ft_getenv(env, "OLDPWD")));
			write((*tavern)->fd->out, ": No such file or directory\n", 28);
			g_status = 1;
		}
		return ;
	}
	oldpwd_update(env, curwd, 1);
	pwd_update(env);
	redefine_pwd(pwd, ft_getenv(env, "OLDPWD"), env, 0);
}

void	cd_path(t_cmd **tavern, t_env **env, char **pwd, char *curwd)
{
	oldpwd_update(env, NULL, 0);
	if (chdir((*tavern)->cmd[1]) != 0)
	{
		write((*tavern)->fd->out, "minishell: cd: ", 15);
		write((*tavern)->fd->out, (*tavern)->cmd[1],
			ft_strlen((*tavern)->cmd[1]));
		write((*tavern)->fd->out, ": No such file or directory\n", 28);
		g_status = 1;
		return ;
	}
	if (!getcwd(curwd, PATH_MAX))
	{
		write((*tavern)->fd->out, 
			"cd: error retrieving current directory: ", 41);
		write((*tavern)->fd->out, 
			"getcwd : cannot access parent directories: \
			No such file or directory\n", 70);
		g_status = 1;
		redefine_pwd(pwd, (*tavern)->cmd[1], env, 1);
		return ;
	}
	pwd_update(env);
	redefine_pwd(pwd, (*tavern)->cmd[1], env, 0);
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
