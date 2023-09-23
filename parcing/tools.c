/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:55:29 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/23 01:56:29 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int white_space(char c)
{
    if(c == ' ' || c == '\t' || c == '\n' || c == '\r'
    || c ==  '\f' || c == '\v')
        return(1);
    return(0);
}

char *fill_word(char *b, int *i, t_env *env)
{
    char *f;
    char *var;
    int l;
    int s;
    int k;

    l = 0;
    s = (*i);
    while (b[(*i)] && b[(*i)] != '>' && b[(*i)] != '<' && b[(*i)] != 39 && b[(*i)] != '|' && b[(*i)] != 34 && !white_space(b[(*i)]))
    {
        if (b[(*i)] == '$')
        {
            var = check_if_valid(b, i, env);
            if (var != NULL)
                l += ft_strlen(var);
        }
        else
            l++;
        (*i)++;
    }
    f = malloc(sizeof(char) * l +1);
    f[l] = '\0';
    k = 0;
    while(l)
    {
        if (b[s] == '$' && var != NULL)
        {
            fill_expand(f, &k, var);
            s++;
            l -= ft_strlen(var);
        }
        else if (b[s] == '$' && var == NULL)
            return (NULL);
        if(l)
        {
            f[k++] = b[s++];
            l--;
        }
    }
    (*i)--;
    return (f);
}

