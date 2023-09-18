/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:11:22 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/18 11:17:19 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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

t_tokens *tokenizer(char *b, t_tokens *list)
{
    int i;
    t_tokens *node;

    i = -1;
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
            node->tokens = "<<";
        else if ((node->type = token(b[i], b[i + 1])) == SQUAT)
            node->tokens = fill_token(b, &i, 34);
        else if ((node->type = token(b[i], b[i + 1])) == DQOUT)
            node->tokens = fill_token(b, &i, 39);
        else if ((node->type = token(b[i], b[i + 1])) == APPEND)
            node->tokens = ">>";
        else if ((node->type = token(b[i], b[i + 1])) == OUT)
            node->tokens = ">";
        else if ((node->type = token(b[i], b[i + 1])) == IN)
            node->tokens = "<";
        else
            node->tokens = fill_word(b, &i);
        add_node(&list, node);
    }
    node = create_node();
    node->type = NLINE;
    add_node(&list, node);
    return (list);
}
int syntax_error(t_tokens *list)
{
    while(list->next)
    {
        if((is_token(list->type) && is_word(list->next->type)))
            return (printf("syntax error : %s\n", list->tokens), list->type = 0 ,  -1);
        else
            list = list->next;
    }
    return (0);
}

int main()
{
    t_cmd *tmp;
    int n_cmd;
    int flg;
    t_cmd *f_list;
    t_tokens *list;
    char *b;
    
    f_list = create_list();
    tmp = f_list;
    while(1)
    {
        list = NULL;
        b = readline("minishell$ ");
        if(b == NULL)
            break;
        if (ft_strlen(b))
            add_history(b);
        list = tokenizer(b, list);
        syntax_error(list);
        while(list)
        {
            add_list(&tmp, create_list());
            int i = -1;
            flg = -1;
            while(list && list->type != NLINE && list->type != PIPE)
            {
                if(!++flg)
                {
                    n_cmd = n_of_cmd(list);
                    tmp->cmd = malloc(sizeof(char *) * (n_cmd + 1));
                    tmp->cmd[n_cmd] = NULL;
                }
                fill(&list, tmp, &i);
            }
            // printf("tmp in null is : =%s=\n", tmp->cmd[1]);
            tmp = tmp->next;
            list = list->next;
        }
        tmp = f_list;
        while (tmp->cmd)
        {
            int i = -1;
            while(tmp->cmd[++i])
            {
                printf("f _ list - :%s\n", tmp->cmd[i]);
            }
            printf("fd_out is %d | fd_in is %d\n", tmp->fd_out, tmp->fd_in);
            tmp = tmp->next;
        }
        
    }

    
    return(0);
}
