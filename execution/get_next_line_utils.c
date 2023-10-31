/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 01:31:52 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/26 11:43:50 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lnode;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lnode = ft_lstlast(*lst);
	lnode -> next = new;
}

t_list	*ft_lstnew(char *content, ssize_t readed)
{
	t_list	*node1;
	int		i;

	if (readed == 0 || !content)
		return (NULL);
	node1 = (t_list *)my_malloc(sizeof(t_list), 1, 1);
	if (!node1)
		return (NULL);
	node1 -> next = NULL;
	node1->content = my_malloc((readed + 1), 1, 1);
	if (!node1->content)
		return (NULL);
	i = -1;
	while (content[++i] && i < readed)
		node1->content[i] = content[i];
	node1->content[i] = '\0';
	return (node1);
}

int	ft_lstchr(t_list *head, char *s, int v)
{
	int		i;
	t_list	*current;

	if (v == 0)
	{
		while (s[v])
			v++;
		return (v);
	}
	if (!head)
		return (0);
	current = ft_lstlast(head);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*allocate_to_line(t_list *stash)
{
	int		i;
	int		len;
	char	*line;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	line = my_malloc((len + 1), 1, 1);
	if (!line)
		return (NULL);
	return (line);
}

void	ft_lstclear(t_list *lst)
{
	t_list	*node;
	t_list	*n_node;

	if (!lst)
		return ;
	node = lst;
	while (node)
	{
		free(node->content);
		n_node = node->next;
		free (node);
		node = n_node;
	}
}
