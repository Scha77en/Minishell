/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:55:29 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/21 15:19:35 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int white_space(char c)
{
    if(c == ' ' || c == '\t' || c == '\n' || c == '\r'
    || c ==  '\f' || c == '\v')
        return(1);
    return(0);
}

char *fill_word(char *b, int *i)
{
    char *f;
    char *env;
    int l;
    int s;
    int k;

    l = 0;
    s = (*i);
    while (b[(*i)] && b[(*i)] != '>' && b[(*i)] != '<' && b[(*i)] != 39 && b[(*i)] != '|' && b[(*i)] != 34 && !white_space(b[(*i)]))
    {
        if (b[(*i)] == '$')
        {
            env = check_if_valid(b, i+1);
            if (env != NULL)
                l += ft_strlen(env);
        }
        (*i)++;
        l++;
    }
    f = malloc(sizeof(char) * l +1);
    f[l] = '\0';
    k = 0;
    while(l)
    {
        if (b[s] == '$' && env != NULL)
        {
            fill_expand(&f, &k, env);
            s++;
        }
        f[k++] = b[s++];
        l--;
    }
    (*i)--;
    return (f);
}
