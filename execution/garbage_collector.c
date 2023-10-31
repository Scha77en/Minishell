#include "../includes/minishell.h"

// void	*my_malloc(size_t size, int v)
// {
// 	static t_mem	*mem;
// 	t_mem	*new_mem;
// 	char	*ptr;

// 	ptr = malloc(size);
// 	if (v >= 0 && ptr)
// 	{
// 		puts("3");
// 		new_mem = malloc(sizeof(t_mem));
// 		if (new_mem)
// 		{
// 			new_mem->ptr = ptr;
// 			new_mem->next = mem;
// 			mem = new_mem;
// 			// ft_lstadd_back_mem(&mem, new_mem);
// 			return (ptr);
// 		}
// 		else
// 		{
// 			free(ptr);
// 			return (NULL);
// 		}
// 	}
// 	else
// 	{
// 		clean_mem(mem);
// 		return (NULL);
// 	}
// }

// void	ft_lstadd_back_mem(t_mem **lst, t_mem *new)
// {
// 	t_mem	*tmp;

// 	if (!*lst)
// 		*lst = new;
// 	else
// 	{
// 		tmp = *lst;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 	}
// 	new->next = NULL;
// }

// void	clean_mem(t_mem *mem)
// {
// 	if (!mem)
// 		return;
// 	clean_mem(mem->next);
// 	free(mem->ptr);
// 	free(mem);
// 	puts("1");
// 	// while (mem)
// 	// {
// 	// 	tmp = mem;
// 	// 	mem = mem->next;
// 	// 	free(tmp->ptr);
// 	// 	free(tmp);
// 	// }
// }

// void	leaks(void)
// {
// 	system("leak a.out");
// }

void clean_mem(t_mem *head)
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
		// exit(1);
	}
	tmp = malloc(sizeof(t_mem));
	if (!tmp)
	{
		free(ptr);
		clean_mem(head);
		// exit(1);
	}
	tmp->ptr = ptr;
	tmp->next = head;
	head = tmp;
	return (ptr);
}

// int main(void)
// {
// 	// atexit(leaks);
// 	t_cmd	*tavern;
// 	char	**word;

// 	tavern = garbage(sizeof(t_cmd), 1, 1);
// 	tavern->cmd = garbage(sizeof(char *), 2, 0);
// 	word = garbage(sizeof(char *) ,2, 0);
// 	garbage(sizeof(char *) , 2, 0);
// }
