/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:45:33 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/21 20:45:09 by abouregb         ###   ########.fr       */
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
void fill_expand(char **f, int *k, char *value)
{
    int i;

    i = -1;
    printf("var before is : %s\n", value);
    while(++i < 4)
    {
        *f[(*k)++] = value[i];
        printf("*[%c]\n", *f[(*k) -1]);//Why one time ????????
    }
}
