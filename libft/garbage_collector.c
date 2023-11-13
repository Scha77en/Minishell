/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:19:26 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/13 15:19:42 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_mem(t_mem *head)
{
	if (!head)
		return ;
	clean_mem(head->next);
	free(head->ptr);
	free(head);
}

void	*my_malloc(int size, int len, int status)
{
	static t_mem	*head;
	void			*ptr;
	t_mem			*tmp;

	ptr = NULL;
	if (status == 1)
	{
		ptr = ft_calloc(size, len);
	}
	if (!ptr || status == 0)
	{
		clean_mem(head);
	}
	tmp = malloc(sizeof(t_mem));
	if (!tmp)
	{
		free(ptr);
		clean_mem(head);
	}
	tmp->ptr = ptr;
	tmp->next = head;
	head = tmp;
	return (ptr);
}
