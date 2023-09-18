/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:19:02 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/18 11:37:16 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void rederections(t_tokens **list, t_cmd *tmp)
{
    t_tokens *t_lst;
    t_lst = *list;
    if(t_lst->type == IN || t_lst->type == HEREDOC)
    {
        t_lst = t_lst->next;
        if (t_lst->type == WHITESPACE)
            t_lst = t_lst->next;
        if (t_lst->type == IN)
            tmp->fd_in = open(t_lst->tokens, O_RDONLY);
        else
            tmp->fd_in = open(t_lst->tokens, O_CREAT | O_WRONLY | O_TRUNC, 0777);//herdock
        if (tmp->fd_in == -1)
        {
            perror("fd_in : Permission denied  .\n");
            exit(1);
        }
    }
    else if (t_lst->type == OUT || t_lst->type == APPEND)
    {
        t_lst = t_lst->next;
        if (t_lst->type == WHITESPACE)
            t_lst = t_lst->next;
        if (t_lst->type == OUT)
            tmp->fd_out = open(t_lst->tokens,O_CREAT | O_WRONLY | O_TRUNC, 0777);
        else
            tmp->fd_out = open(t_lst->tokens, O_CREAT | O_WRONLY | O_APPEND, 0777);
        if (tmp->fd_out == -1)
        {
            perror("fd_out : Permission denied  .\n");
            exit(1);
        }
    }
    *list = t_lst;
}