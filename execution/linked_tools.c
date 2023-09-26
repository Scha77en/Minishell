/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:45:33 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/23 02:07:14 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../parcing/msh.h"

t_cmd	*ft_lstnew_m(char *content)
{
	t_cmd	*node1;

	node1 = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node1)
		return (0);
	node1 -> cmd = &content;
    node1 -> fd_in = 0;
    node1 -> fd_out = 1;
	node1 -> next = NULL;
	// node1 -> previous = NULL;
	return (node1);
}

void	ft_lstadd_back_m(t_data **lst, t_data *new)
{
	t_data	*lnode;

	if (!new)
		return ;
	while (!*lst)
	{
		*lst = new;
		return ;
	}
	lnode = ft_lstlast_m(*lst);
	lnode -> next = new;
}

t_data	*ft_lstlast_m(t_data *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
