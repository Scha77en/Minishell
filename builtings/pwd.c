/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 06:55:04 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/12 11:12:34 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_working_directory(t_cmd **tavern, char **pwd)
{
	char	current_directory[PATH_MAX];

	if (getcwd(current_directory, sizeof(current_directory)) != NULL)
	{
		write((*tavern)->fd->out, current_directory,
			ft_strlen(current_directory));
	}
	else
	{
		write((*tavern)->fd->out, *pwd, ft_strlen(*pwd));
	}
	write((*tavern)->fd->out, "\n", 1);
}

void	redefine_pwd(char **pwd, char *define, t_env **env, int v)
{
	if (v == 1)
	{
		v = 0;
		while (define[v])
			v++;
		if (define[v - 1] == '/')
			define[v - 1] = '\0';
		*pwd = ft_strjoin_b(*pwd, ft_strdup(define), 1);
	}
	else
		*pwd = ft_strdup(ft_getenv(env, "PWD"));
}
