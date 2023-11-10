/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:26:20 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/10 20:14:34 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*_var(char **env, int n, int *s)
{
	int		i;
	char	*var;

	i = -1;
	var = my_malloc((var_len(env[n]) + 1), sizeof(char), 1);
	var[var_len(env[n])] = '\0';
	while (env[n][++i] != '=')
		var[i] = env[n][i];
	*s = i + 1;
	return (var);
}
char *_value(char **env, int n, int *s)
{
	int i;
	char *value;

	i = -1;
	value = my_malloc((valu_len(env[n], *s) + 1), sizeof(char), 1);
	if (!value)
		return (NULL);
	value[valu_len(env[n], *s)] = '\0';
	while (env[n][*s])
		value[++i] = env[n][(*s)++];
	return (value);
}

t_env	*envirement(char **env)
{
	int		s;
	int		n;
	t_env	*nv;
	t_env	*head;

	n = 0;
	nv = NULL;
	while (env[n])
	{
		if (!ft_strncmp(env[n], "OLDPWD", 6))
			n++;
		ft_lstaddback(&nv, lstnew());
		if (!n)
			head = nv;
		else
			nv = nv->next;
		nv->var = _var(env, n, &s);  
		nv->value = _value(env, n, &s);
		n++;
	}
	return (head);
}
