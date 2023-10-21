/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:46:55 by aouhbi            #+#    #+#             */
/*   Updated: 2023/10/19 18:53:09 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	main(int argc, char **argv, char **env)
// {
// 	t_cmd	*current;
// 	t_cmd	*tavern;
// 	t_cmd	*node1;
// 	t_cmd	*node2;
// 	t_cmd	*node3;
// 	// int		i;

// 	// i = 0;
// 	// while (env[i])
// 	// {
// 	// 	printf("%s\n", env[i]);
// 	// 	i++;
// 	// }
// 	char **s1 = malloc(2 * sizeof(char *)); // Allocate memory for the array of pointers
// 	s1[0] = ft_strdup("ls");                   // Allocate memory for the string and copy it
// 	s1[1] = NULL;        	               // Terminate the array with NULL

// 	char **s2 = malloc(2 * sizeof(char *));
// 	s2[0] = ft_strdup("cat");
// 	s2[1] = NULL;

// 	char **s3 = malloc(2 * sizeof(char *));
// 	s3[0] = ft_strdup("wc");
// 	s3[1] = NULL;

// 	tavern = NULL;
// 	ft_lstadd_back_t(&tavern, ft_lstnew_t(s1, 0, 1));
// 	// ft_lstadd_back_t(&tavern, ft_lstnew_t(s2, fd, 1));
// 	// ft_lstadd_back_t(&tavern, ft_lstnew_t(s3, 0, 1));
// 	// printf("[%s]\n", tavern->cmd[0]);
// 	// current = tavern;
// 	// while (current)
// 	// {
// 	// 	printf("cmd = [%s]\n", current->cmd[0]);
// 	// 	current = current->next;
// 	// }
// 	int fd = open("new_file", O_CREAT | O_WRONLY | O_TRUNC, 0777);
// 	tavern->fd->out = fd;
// 	execute_cmds(tavern, env);
// 	free(s1[0]);
// 	free(s1);
// 	free(s2[0]);
// 	free(s2);
// 	free(s3[0]);
// 	free(s3);
// }

t_cmd	*ft_lstnew_t(char **content, int fd_in, int fd_out)
{
	t_cmd	*node1;

	node1 = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node1)
		return (0);
	// printf("%s\n", content);
	node1->cmd = content;
	node1->fd->in = fd_in;
	node1->fd->out = fd_out;
	node1->next = NULL;
	return (node1);
}

void	ft_lstadd_back_t(t_cmd **lst, t_cmd *new)
{
	t_cmd	*lnode;

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

t_cmd	*ft_lstlast_t(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// char	*ft_strdup(char *s1)
// {
// 	char	*ptr;
// 	size_t	slen;

// 	slen = ft_strlen_m(s1) + 1;
// 	ptr = (char *)malloc(slen);
// 	if (!ptr || !s1)
// 		return (0);
// 	ft_memcpy(ptr, s1, (size_t)slen);
// 	return (ptr);
// }

void	*ft_memcpy_m(void *dst, void *src, size_t n)
{
	size_t	i;
	char	*s;
	char	*d;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	if (src == 0 && dst == 0)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
