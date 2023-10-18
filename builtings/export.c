/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 03:10:54 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/30 14:47:07 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(t_cmd *tavern, t_env **env)
{
	int		i;
	char	**split;

	i = 1;
	if (tavern->cmd[i] == NULL)
		ft_env(env, 1);
	else
	{
		while (tavern->cmd[i] != NULL)
		{
			if(check_validity(tavern->cmd[i]))
			{
				split = split_export(tavern->cmd[i]);
				if (split[1] == NULL)
					ft_add_env(env, split);

				else if(plus_sign(split[0], 0) > 0)
					ft_join_value(env, split);
				else
					ft_add_env(env, split);
			}
			else
				printf("Minishell: export: `%s': not a valid identifier\n", tavern->cmd[i]);
			i++;
		}
	}
}

// it must skip one \ and return an error when more than one \ is found in the var;

int	check_validity(char *str)
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
		if ((ft_isdigit(str[i]) == 0 && alpha_undscore(str[i])) || back_slash(str))
			return (0);
	}
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
	t_env	*current;
	char	*join;
	size_t		k;

	join = NULL;
	current = *env;
	k = ft_strlen(split[0]);
	while (current)
	{
		if (!ft_strncmp(current->var, split[0], k - 1))
		{
			join = ft_strjoin(current->value, split[1]);
			free(current->value);
			current->value = ft_strdup(join);
			free(join);
			return ;
		}
		current = current->next;
		if (current == NULL)
			break ;
	}
	ft_add_env(env, split);
}

void	ft_add_env(t_env **env, char **split)
{
	t_env	*current;
	t_env	*new;

	if (!env)
	{
		*env = ft_envnew(split[0], split[1]);
		return ;
	}
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->var, split[0]) == 0)
		{
			free(current->value);
			if (split[1] == NULL)
				current->value = ft_strdup("");
			else
				current->value = ft_strdup(split[1]);
			return ;
		}
		current = current->next;
	}
	new = malloc(sizeof(t_env));
	if (plus_sign(split[0], 1))
		new->var = ft_strndup(split[0], (plus_sign(split[0], 1)));
	else
		new->var = ft_strdup(split[0]);
	new->value = ft_strdup(split[1]);
	new->next = NULL;
	ft_lstaddback(env, new);
}

char	*ft_strndup(char *s, int n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(n + 1 * sizeof(char));
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