/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:26:20 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/30 00:25:39 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*lstnew()
{
	t_env	*link;

	if (!(link = my_malloc(sizeof(t_env), 1, 1)))
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

t_env	*envirement(char **env)
{
	int		i;
	int		s;
	int		n;
	int		check;
	t_env	*nv;
	t_env	*head;

	n = 0;
	i = 0;
	check = 0;
	nv = NULL;
	while (env[n])
	{
		if (!ft_strncmp(env[n], "OLDPWD", 6))
			n++;
		ft_lstaddback(&nv, lstnew());
		if (!check++)
			head = nv;
		else
			nv = nv->next;
		i = -1;
		nv->var = my_malloc((var_len(env[n]) + 1), sizeof(char), 1);
		nv->var[var_len(env[n])] = '\0';
		while (env[n][++i] != '=')
			nv->var[i] = env[n][i];
		s = i + 1;     
		i = -1;
		nv->value = my_malloc((valu_len(env[n], s) + 1), sizeof(char), 1);
		if (!nv->value)
			return (printf("fiell\n"), NULL);
		nv->value[valu_len(env[n], s)] = '\0';
		while (env[n][s])
			nv->value[++i] = env[n][s++];
		n++;
	}
	return (head);
}
