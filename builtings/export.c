/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 03:10:54 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/13 20:46:44 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(t_cmd *tavern, t_env **env)
{
	int		i;
	int		v;

	i = 1;
	v = 0;
	if (tavern->cmd[i] == NULL)
		ft_env(&tavern, env, 1);
	else
	{
		while (tavern->cmd[i] != NULL)
		{
			if (check_validity(tavern->cmd[i], &v))
				manage_the_export(tavern, env, v, i);
			else
			{
				write(2, "minishell: export: `", 20);
				ft_putstr_fd(tavern->cmd[i], 2);
				write(2, "': not a valid identifier\n", 26);
				g_status = 1;
			}
			i++;
		}
	}
}

void	manage_the_export(t_cmd *tavern, t_env **env, int v, int i)
{
	char	**split;

	split = split_export(tavern->cmd[i]);
	if (split[1] == NULL)
		ft_add_env(env, split, v);
	else if (plus_sign(split[0], 0) > 0)
		ft_join_value(env, split);
	else
		ft_add_env(env, split, v);
	g_status = 0;
}

int	check_validity(char *str, int *v)
{
	int	i;

	i = 0;
	if (alpha_undscore(str[0]))
		return (0);
	while (str[++i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		if (str[i] == '=')
			return (1);
		if ((ft_isdigit(str[i]) == 0 && alpha_undscore(str[i]))
			|| back_slash(str))
			return (0);
	}
	*v = 2;
	return (1);
}

int	back_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == 92 && str[i + 1] == 92)
			return (1);
		i++;
	}
	return (0);
}

int	alpha_undscore(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == 92)
		return (0);
	return (1);
}
