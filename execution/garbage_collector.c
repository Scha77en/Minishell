#include "../includes/minishell.h"

void	*my_malloc(size_t size, t_mem **mem)
{
	t_mem	*new_mem;

	new_mem = malloc(sizeof(t_mem));
	if (!new_mem)
		error_out("malloc", 1);
	new_mem->ptr = malloc(size);
	if (!new_mem->ptr)
		error_out("malloc", 1);
	ft_lstadd_back_mem(mem, new_mem);
	return (new_mem->ptr);
}

void	ft_lstadd_back_mem(t_mem **lst, t_mem *new)
{
	t_mem	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->next = NULL;
}

void	clean_mem(t_mem **mem)
{
	t_mem	*tmp;

	while(*mem)
	{
		tmp = *mem;
		*mem = (*mem)->next;
		free(tmp->ptr);
		free(tmp);
	}
	mem = NULL;
}

// void	leaks(void)
// {
// 	system("leak a.out");
// }

// int main(void)
// {
// 	// atexit(leaks);
// 	t_mem	*mem;
// 	t_cmd	*tavern;
// 	char	**word;

// 	mem = NULL;
// 	tavern = my_malloc(sizeof(t_cmd), &mem);
// 	tavern->cmd = my_malloc(sizeof(char *) * 2, &mem);
// 	word = my_malloc(sizeof(char *) * 2, &mem);
// 	// while(1);
// 	// clean_mem(&mem);
// }
