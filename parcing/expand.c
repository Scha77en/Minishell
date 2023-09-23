/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:45:33 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/23 18:53:28 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int find_exp(char *s, int i, char c)
{
    printf("i :\n");
    while(s[i] != c)
    {
        printf("in\n");
        if(s[i] == '$')
            return(i);
        i++;
    }
    return(-1);
}
char *compare(char *var, t_env *env)
{
    while(env)
    {
        if(ft_strncmp(var, env->var, ft_strlen(var)) == 0)
        {
            printf("am here\n");
            return (env->value);
        }
        env = env->next;       
    }
    return (NULL);
}
char *check_if_valid(char *str, int *i ,t_env *env)
{
    int s;
    int n;
    char *var;
    (*i)++;
    s = (*i);
    n = 0;
    while(str[(*i)] && (ft_isalpha(str[(*i)]) || str[(*i)] == '_'))
    {
        (*i)++;
        n++;
    }
    var = malloc(sizeof(char) * (n +1));
    n = 0;
    while(s < *i)
        var[n++] = str[s++];
    var[n] = '\0';
    var = compare(var, env);
    return (var);
}
void fill_expand(char *f, int *k, char *value)
{
    int i;

    i = 0;
    while(value[i])
        f[(*k)++] = value[i++];
}
