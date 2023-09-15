#include "../includes/minishell.h"

t_data	*ft_lstnew_m(char *content, int v)
{
	t_data	*node1;

	node1 = (t_data *)malloc(sizeof(t_data));
	if (!node1)
		return (0);
	node1 -> cmd = content;
    node1 -> type = v;
	node1 -> next = NULL;
	node1 -> previous = NULL;
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
