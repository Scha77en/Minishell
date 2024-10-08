/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:25:18 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/14 16:12:18 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*copy_env_list(t_env **env)
{
	t_env	*head;
	t_env	*curr;

	head = NULL;
	curr = *env;
	while (curr)
	{
		add_env(&head, curr->var, curr->value, curr->id);
		curr = curr->next;
	}
	return (head);
}

void	sort_env(t_env *env)
{
	t_env	*current;
	t_env	*front;
	char	*temp;
	int		v;

	v = 0;
	temp = NULL;
	current = env;
	while (current)
	{
		front = current->next;
		while (front)
		{
			if (ft_strncmp(current->var, front->var, 
					ft_strlen(current->var) + 1) > 0)
				swap_env(v, current, front, temp);
			front = front->next;
		}
		current = current->next;
	}
}

void	swap_env(int v, t_env *current, t_env *front, char *temp)
{
	temp = current->var;
	current->var = front->var;
	front->var = temp;
	temp = current->value;
	current->value = front->value;
	front->value = temp;
	v = current->id;
	current->id = front->id;
	front->id = v;
}

void	add_env(t_env **env, char *var, char *value, int v)
{
	t_env	*new;
	t_env	*current;

	new = my_malloc(sizeof(t_env), 1, 1);
	new->var = ft_strdup(var);
	new->value = ft_strdup(value);
	new->id = v;
	new->next = NULL;
	if (!(*env))
		*env = new;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = new;
	}
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
