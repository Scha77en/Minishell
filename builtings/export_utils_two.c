/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:10:54 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/12 11:30:09 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	plus_sign(char *str, int v)
{
	int	i;

	i = 0;
	if (v == 0)
	{
		while (str[i])
		{
			if (str[i] == '=')
				return (0);
			if (str[i] == '+' && str[i + 1] == '\0')
				return (i);
			i++;
		}
	}
	else
	{
		while (str[i])
		{
			if (str[i] == '+')
				return (i);
			i++;
		}
	}
	return (0);
}

void	ft_join_value(t_env **env, char **split)
{
	t_env		*current;
	char		*join;
	size_t		k;

	join = NULL;
	current = *env;
	k = ft_strlen(split[0]);
	while (current)
	{
		if (!ft_strncmp(current->var, split[0], k - 1))
		{
			join = ft_strjoin(current->value, split[1]);
			current->value = ft_strdup(join);
			return ;
		}
		current = current->next;
		if (current == NULL)
			break ;
	}
	ft_add_env(env, split, 0);
}

void	ft_add_env(t_env **env, char **split, int v)
{
	t_env	*current;

	if (!env)
	{
		*env = ft_envnew(split[0], split[1]);
		(*env)->id = v;
		return ;
	}
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->var, split[0],
				ft_strlen(current->var) + 1) == 0)
		{
			if (split[1] == NULL)
				current->value = ft_strdup("");
			else
				current->value = ft_strdup(split[1]);
			current->id = v;
			return ;
		}
		current = current->next;
	}
	adding_new_env(env, split, v);
}

void	adding_new_env(t_env **env, char **split, int v)
{
	t_env	*new;

	new = my_malloc(sizeof(t_env), 1, 1);
	if (plus_sign(split[0], 1))
		new->var = ft_strndup(split[0], (plus_sign(split[0], 1)));
	else
		new->var = ft_strdup(split[0]);
	new->value = ft_strdup(split[1]);
	new->id = v;
	new->next = NULL;
	ft_lstaddback(env, new);
}

char	*ft_strndup(char *s, int n)
{
	char	*str;
	int		i;

	i = 0;
	str = my_malloc((n + 1), 1, 1);
	if (!str)
		return (NULL);
	while (s[i] && i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
