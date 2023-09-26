/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:22:41 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/26 08:42:47 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int token(char fc, char sc)
{
    if(fc == '|')
       return (PIPE); 
    else if (fc == 39)
        return (DQOUT);
    else if (fc == 34)
        return (SQUAT);
    else if (fc == '>' && sc == '>')
        return (APPEND);
    else if (fc == '<' && sc == '<')
        return (HEREDOC);
    else if (fc == '<' && sc != '<')
        return (IN);
    else if (fc == '>' && sc != '>')
        return (OUT);
    else if (fc == ' ')
        return(WHITESPACE);
    else
       return (WORD);
}

char *fill_token(char *b, int *i, char c)
{
    char *filed;
    char *var;
    int len;
    int n;
    int lv;
    n = 0;
    var = NULL;
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
            if (!ft_strlen(var))
                len++;
        }
        else
            len++;
    }
    if (var != NULL)
        len += (ft_strlen(var) - lv) - (*i +1);
    filed = malloc(sizeof(char ) * len);
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
            *i = len;
        }
        else
        {
            filed[n++] = b[len++];
            (*i)++;
        }
    }
    filed[n] = '\0';
    return(filed);
}

char *fill_var(char *b, int n, int len)
{
    int i;
    char *var;

    i = 0;
    var = malloc(sizeof(char) * (n - len) + 1);
    var[(n - len)] = '\0';
    n = len +1;
    while(b[n] && (ft_isalpha(b[n]) || b[n] == '_'))
    {
        var[i++] = b[n++];
    }
    return (var);
}
int is_word(int type)
{
    if(type == WORD || type == SQUAT
    || type == DQOUT)
        return (1);
    return (0);
}

int is_token(int type)
{
    if(type == PIPE || type == IN || type == OUT
    || type == HEREDOC || type == APPEND)
        return (1);
    return (0);
}
