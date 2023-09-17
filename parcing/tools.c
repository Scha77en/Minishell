/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:55:29 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/06 09:33:39 by abouregb         ###   ########.fr       */
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
    int l;
    int s;
    int k;

    l = 0;
    s = (*i);
    while (b[(*i)] && b[(*i)] != '>' && b[(*i)] != '<' && b[(*i)] != 39 && b[(*i)] != '|' && b[(*i)] != 34 && !white_space(b[(*i)]))
    {
        (*i)++;
        l++;
    }
    f = malloc(sizeof(char) * l +1);
    f[l] = '\0';
    k = 0;
    while(l)
    {
        f[k++] = b[s++];
        l--;
    }
    (*i)--;
    return (f);
}
