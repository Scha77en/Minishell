/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:12:15 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/29 15:18:41 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens *create_node()
{
    t_tokens *node;

    node = malloc(sizeof(t_tokens));
    if (!node)
        return (NULL);
    node->tokens = NULL;
    node->next = NULL;
    return (node);
}

void add_node(t_tokens **list, t_tokens *new)
{
    t_tokens *tmp;

    
    if (!(*list))
        *list = new;
    else
    {
        tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

t_tokens *tokenizer(char *b, int *exit_status)
{
    int i;
    t_tokens *list;
    t_tokens *node;

    i = -1;
    list = NULL;
    while (b[++i])
    {
        node = create_node();
        if ((node->type = token(b[i], ' ')) == WHITESPACE)
        {
            node->tokens = " ";
            while(white_space(b[i+1]))
                i++;
        }
        else if ((node->type = token(b[i], b[i + 1])) == PIPE)
            node->tokens = "|";
        else if ((node->type = token(b[i], b[i + 1])) == HEREDOC)
        {
            node->tokens = "<<";
            i++;
        }
        else if ((node->type = token(b[i], b[i + 1])) == APPEND)
        {
            node->tokens = ">>";
            i++;
        }
        else if ((node->type = token(b[i], b[i + 1])) == SQUAT)
        {
            if ((node->tokens = fill_token(b, &i, 34, exit_status)) == NULL)
                return (NULL);            
        } 
        else if ((node->type = token(b[i], b[i + 1])) == DQOUT)
        {
            if ((node->tokens = fill_token(b, &i, 39, exit_status)) == NULL)
                return (NULL); 
        }
        else if ((node->type = token(b[i], b[i + 1])) == OUT)
            node->tokens = ">";
        else if ((node->type = token(b[i], b[i + 1])) == IN)
            node->tokens = "<";
        else
            node->tokens = fill_word(b, &i, exit_status);
        add_node(&list, node);
    }
    node = create_node();
    node->type = NLINE;
    add_node(&list, node);
    // free(node);
    return (list);
}
int syntax_error(t_tokens *list)
{
    while(list)
    {
        if((is_token(list->type) && !is_word(list->next->type)
        && list->next->type != WHITESPACE))
            return (printf("syntax error : %s\n", list->tokens), list->type = 0 , 258);
        // else if (is_token(list->type) && !is_word(list->next->next->type))
        //     return (printf("syntax error : %s\n", list->tokens), list->type = 0 ,  -1);
        else
            list = list->next;
    }
    return (0);
}
