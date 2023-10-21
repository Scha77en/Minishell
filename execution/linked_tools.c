/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:45:33 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/23 03:19:48 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_lstnew_m(char *content)
{
	t_cmd	*node1;

	node1 = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node1)
		return (0);
	node1 -> fd = (t_fd *)malloc(sizeof(t_fd));
	node1 -> cmd = &content;
	node1->next = NULL;
	// node1 -> previous = NULL;
	return (node1);
}

void	ft_lstadd_back_m(t_data **lst, t_data *new)
{
	t_data	*lnode;

	if (!new)
		return ;
	if (!*lst)
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

int	ft_lstsize(t_cmd *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
