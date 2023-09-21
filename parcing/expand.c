/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:45:33 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/21 01:32:08 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int find_exp(char *s, int i, char c)
{
    while(s[i] != c)
    {
        if(s[i] == '$')
            return(i+1);
        i++;
    }
    return(-1);
}
int check_if_valid(char *str, int i)
{
    int s;
    int n;
    char *var;

    s = i;
    n = 0;
    while(str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
    {
        i++;
        n++;
    }
    printf("n : %c\n", str[i]);
    var = malloc(sizeof(char) * n +1);
    n = 0;
    while(s <= i)
        var[n++] = str[s++];
    var[n] = '\0';
    printf("var : %s\n", var);
    return (0);
}
