/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:46:55 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/17 03:00:47 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **env)
{
	t_cmd	*current;
	t_cmd	*final;
	t_cmd	*node1;
	t_cmd	*node2;
	t_cmd	*node3;

	char	*s1 = strdup("ls -la");
	char	*s2 = strdup("cat");
	char	*s3 = strdup("wc -l");

	final = NULL;
	ft_lstadd_back_t(&final, ft_lstnew_t(s1));
	ft_lstadd_back_t(&final, ft_lstnew_t(s2));
	ft_lstadd_back_t(&final, ft_lstnew_t(s3));
	printf("[%s]\n", final->cmds->cmd);
	current = final;
	while (current)
	{
		printf("cmd = [%s]\n", current->cmds->cmd);
		current = current->next;
	}
	execute_cmds(final, env);
}

t_final_list	*ft_lstnew_t(char *content)
{
	t_final_list	*node1;

	node1 = (t_final_list *)malloc(sizeof(t_final_list));
	if (!node1)
		return (0);
	node1->cmds = (t_cmd *)malloc(sizeof(t_cmd)); // Allocate memory for cmds structure
	if (!node1->cmds)
	{
		free(node1); // Clean up and return on allocation failure
		return (0);
	}
	// printf("%s\n", content);
	node1->cmds->cmd = content;
	node1->rederections = NULL;
	node1->next = NULL;
	return (node1);
}

void	ft_lstadd_back_t(t_final_list **lst, t_final_list *new)
{
	t_final_list	*lnode;

	if (!new)
		return ;
	while (!*lst)
	{
		*lst = new;
		return ;
	}
	lnode = ft_lstlast_t(*lst);
	lnode -> next = new;
}

t_final_list	*ft_lstlast_t(t_final_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
