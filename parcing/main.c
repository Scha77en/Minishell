/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:11:22 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/26 07:52:00 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void print_list(t_cmd *f_list)
{
    while (f_list)
    {
        int i = 0;
        while(f_list->cmd[i])
        {
            printf("cmd : %s\n", f_list->cmd[i++]);
        }
        printf("-------------\n");
        f_list = f_list->next;
    }
}
void  parcer(t_tokens **list, t_cmd **f_list)
{
    t_cmd *tmp;
    int flg;
    int n_cmd;

    add_list(f_list, create_list());
    tmp = ft_lstlast_p(*f_list);
    int i = -1;
    flg = -1;
    while((*list) && (*list)->type != NLINE && (*list)->type != PIPE)
    {
        if(!++flg)
        {
            n_cmd = n_of_cmd((*list));
            tmp->cmd = malloc(sizeof(char *) * (n_cmd + 1));
            tmp->cmd[n_cmd] = NULL;
        }
        fill(&(*list), tmp, &i);
    }
    (*list) = (*list)->next;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_tokens *list;
    t_cmd *f_list;
    t_env *envr;
    char *b;

    envr = envirement(env);
    while(1)
    {
        b = readline("minishell$ ");
        if(b == NULL)
            break;
        if (ft_strlen(b))
        {
            add_history(b);
            list = tokenizer(b);
            if (syntax_error(list) == -1)
                list = NULL;
            f_list = NULL;
            while(list)
                parcer(&list, &f_list);
            if (f_list != NULL)
                print_list(f_list);
        }
    }
    return(0);
}
