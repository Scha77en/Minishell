/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenat_Words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:33:54 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/28 21:53:06 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens *concatenat_words(t_tokens *list)
{
    char *word;
    t_tokens *current;
    current = NULL;
    t_tokens *node;
    while (list)
    {
        node = create_node();
        if (is_word(list->type))
        {
            word = list->tokens;
            while(is_word(list->next->type))
            {
                word = ft_strjoin(list->tokens, list->next->tokens);
                list = list->next;
            }
            node->tokens = word;
            node->type = WORD;
        }
        else
        {
            node->tokens = list->tokens;
            node->type = list->type;
        }
        add_node(&current, node);
        list = list->next;
    }
    node = create_node();
    node->type = NLINE;
    add_node(&current, node);
    return(current);
}
