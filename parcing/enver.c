/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enver.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:44:05 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/13 15:44:14 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*lstnew(void)
{
	t_env	*link;

	link = my_malloc(sizeof(t_env), 1, 1);
	if (!link)
		return (NULL);
	link->next = NULL;
	link->value = NULL;
	link->var = NULL;
	return (link);
}

void	ft_lstaddback(t_env **hed, t_env *new)
{
	t_env	*ptr;

	if (*hed)
	{
		ptr = *hed;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	else
		*hed = new;
}

int	var_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	return (i);
}

int	valu_len(char *s, int i)
{
	int	r;

	r = 0;
	while (s[i++])
		r++;
	return (r);
}
