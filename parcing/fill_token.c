/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:12:37 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/29 15:21:38 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *fill_token(char *b, int *i, char c, int *exit_status)
{
    char *filed;
    char *var;
    int len;
    int n;
    int lv;
    n = 0;
    var = NULL;
    if (cheak(b, i, c) == 1)
    {
        printf("[%c] :syntax error\n", b[*i]);
        return (NULL);
    }
    len = *i + 1;
    while(b[len] && b[len] != c)
    {
        if(b[len] == '$' && c == 34)
        {
            n = len;
            while(b[n +1] && (ft_isalpha(b[n +1]) || b[n +1] == '_'))
                n++;
            var = fill_var(b, n, len);
            lv = ft_strlen(var);
            len += lv;
            var = getenv(var++);
            if (b[n+1] == '?')
                var = ft_itoa(*exit_status);
            if (!ft_strlen(var))
                len++;
        }
        else
            len++;
    }
    if (var != NULL)
        len += (ft_strlen(var) - lv) - (*i +1);
    filed = malloc(sizeof(char ) * len);
    if (!filed)
        return (NULL);
    n = 0;
    len = *i + 1;
    while(b[len] && b[len] != c)
    {
        if(b[len] == '$' && var != NULL && c == 34)
        {
            size_t v = 0;
            while(v < ft_strlen(var))
                filed[n++] = var[v++];
            len += lv +1;
        }
        else
            filed[n++] = b[len++];
    }
    filed[n] = '\0';
    *i = len;
    return(filed);
}

char *fill_var(char *b, int n, int len)
{
    int i;
    char *var;

    i = 0;
    var = malloc(sizeof(char) * (n - len) + 1);
    if (!var)
        return (NULL);
    var[(n - len)] = '\0';
    n = len +1;
    while(b[n] && (ft_isalpha(b[n]) || b[n] == '_'))
    {
        var[i++] = b[n++];
    }
    return (var);
}