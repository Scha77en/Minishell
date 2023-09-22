/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:22:41 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/22 07:03:15 by aouhbi           ###   ########.fr       */
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
    int s;
    char *fill;
    int k;

    s = *i;
    k = 0;
    fill = NULL;
    while(b[s+1] && b[s+1] != c)
        s++;
    if (b[++s] == c)
    {
        // if(c ==  34 && find_exp(b, (*i)+1, 34) >= 0)
        //     check_if_valid(b, find_exp(b, (*i)+1, 34));
        s = (s - *i);
        fill = malloc(sizeof(char) * s);
        fill[s -1] = '\0';
        while(fill[k] && b[++(*i)] != c)
            fill[k++] = b[(*i)];
        ++(*i);
    }
    else if (b[s] != c)
        printf("SYNTAX : Erorr\n");
    return (fill);
}
int is_word(int type)
{
    if(type == WORD || type == SQUAT || type == DQOUT)
        return (1);
    return (0);
}

int is_token(int type)
{
    if(type == PIPE || type == IN || type == OUT || type == HEREDOC || type == APPEND)
        return (1);
    return (0);
}
