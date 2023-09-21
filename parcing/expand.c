/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:45:33 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/21 15:15:28 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int find_exp(char *s, int *i, char c)
{
    while(s[(*i)] != c)
    {
        if(s[(*i)] == '$')
            return((*i)+1);
        (*i)++;
    }
    return(-1);
}
char *compare(char *var)
{
    t_env *env;
    while(env)
    {
        if(ft_strncmp(var, env->var, ft_strlen(var)) == 0)
            return (env->value);
        env = env->next;       
    }
    return (NULL);
}
char *check_if_valid(char *str, int *i)
{
    int s;
    int n;
    char *var;

    s = (*i);
    n = 0;
    while(str[(*i)] && (ft_isalpha(str[(*i)]) || str[(*i)] == '_'))
    {
        (*i)++;
        n++;
    }
    var = malloc(sizeof(char) * n +1);
    var[n] = '\0';
    n = 0;
    while(s <= (*i))
        var[n++] = str[s++];
    var = compare(var);
    return (var);
}
void fill_expand(char **f, int *k, char *env)
{
    int i;

    i = 0;
    while(env[i])
    {
        *f[(*k++)] = env[i++];
    }
}
