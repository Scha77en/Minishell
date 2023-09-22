/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:26:20 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/22 07:02:39 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*lstnew()
{
	t_env	*link;

	if (!(link = malloc(sizeof(t_env))))
		return (NULL);
	link->next = NULL;
	link->value = NULL;
	link->var = NULL;
	return (link);
}

void ft_lstaddback(t_env **hed, t_env *new)
{
    t_env *ptr;

    if (*hed)
    {
        ptr = *hed;
        while (ptr->next)
            ptr = ptr->next;
        ptr->next = new;  // Assign the new node to the next of the last node
    }
    else
    {
        *hed = new;  // Update the head to point to the new node
    }
}

int var_len(char *var)
{
    int i = 0;
    while(var[i] != '=')
        i++;
    return (i);
}

int valu_len(char *s, int i)
{
    int r;

    r = 0;
    while(s[i++])
        r++;
    return (r);
}

t_env *envirement(char **env)
{
    int i;
    int s;
    int n;
    int check;
    n = 0;
    i = 0;
    check = 0;
    t_env *nv;
    t_env *head;

    nv = NULL;
    while(env[n])
    {
        if(!ft_strncmp(env[n], "OLDPWD", 6))
            n++;
        ft_lstaddback(&nv, lstnew());
        if(!check++)
            head = nv;
        else
            nv = nv->next;
        i = -1;
        nv->var = malloc(sizeof(char) * (var_len(env[n]) + 1));
        nv->var[var_len(env[n])] = '\0';
        while(env[n][++i] != '=')
            nv->var[i] = env[n][i];
        s = i + 1;     
        i = -1;
        nv->value = malloc(sizeof(char) * (valu_len(env[n], s) + 1));
        if(!nv->value)
            return(printf("fiell\n"), NULL);
        nv->value[valu_len(env[n], s)] = '\0';
        while(env[n][s])
            nv->value[++i] = env[n][s++];
        n++;
    }
    return (head);
}
