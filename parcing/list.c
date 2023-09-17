/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:11:44 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/17 20:57:27 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_cmd *create_list()
{
    t_cmd *node;

    node = malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->cmd = NULL;
    node->next = NULL;
    return (node);
}

void add_list(t_cmd **list, t_cmd *new)
{
    t_cmd *tmp;
    tmp = NULL;
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

// t_cmd *ft_lstnew(char *content)
// {
//     t_cmd *node;
//     node = malloc(sizeof(t_cmd));
//     if (!node)
//         return (NULL);
//     node->cmd = content;
//     node->next = NULL;
//     return(node);
// }

// void ft_lstadd_back(t_cmd **lst, t_cmd *new)
// {
//     t_cmd *tmp;
//     if (!*lst)
//     {
//         *lst = new;
//         return ;
//     }
//     tmp = *lst;
//     while(tmp)
//     {
//         printf("d\n");
//         if(!tmp->next)
//         {
//             tmp->next = new;
//             break;
//         }
//         tmp = tmp->next;
//     }
//     // tmp = new;
// }
int n_of_cmd(t_tokens *list)
{
    int r;

    r = 0;
    while(list->type != PIPE && list->type != NLINE)
    {
        if(is_word(list->type) && list->next->type == WHITESPACE)
            r++;
        else if (is_word(list->type) && is_word(list->next->type))
        {
            while(is_word(list->next->type))
                list = list->next;
            r++;
        }
        list = list->next;
    }
    return (r);
}

void fill(t_tokens **list, t_cmd *tmp, int *i)
{
    char *word;

    if (is_word((*list)->type) && is_word((*list)->next->type))
    {
        word = (*list)->tokens;
        while(is_word((*list)->next->type))
        {
            word = ft_strjoin(word, (*list)->next->tokens);
            (*list) = (*list)->next;
        }
        tmp->cmd[++(*i)] = ft_strdup(word);
    }
    else if(is_word((*list)->type) && !is_word((*list)->next->type))
    {
        word = (*list)->tokens;
        tmp->cmd[++(*i)] = ft_strdup(word);
    }
    // else if ((*list)->type == IN || (*list)->type == OUT || (*list)->type == HEREDOC || (*list)->type == APPEND)
    // {
    //     tmp->fd_in = open((*list)->tokens, O_RDONLY);
    // }
    (*list) = (*list)->next;
}
