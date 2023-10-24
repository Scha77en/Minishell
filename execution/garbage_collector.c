#include "../includes/minishell.h"

void	*my_malloc(size_t size, int v)
{
	t_mem	**mem;
	t_mem	*new_mem;
	char	*ptr;

	if (v >= 0)
	{
		mem = malloc(sizeof(t_mem *));
		new_mem = malloc(sizeof(t_mem));
		ptr = malloc(size);
		if (!ptr)
			error_out("malloc", 1);
		new_mem->ptr = ptr;
		new_mem->next = NULL;
		ft_lstadd_back_mem(mem, new_mem);
		return (new_mem->ptr);
	}
	else
	{
		clean_mem(mem);
		return (NULL);
	}
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

	while (*mem)
	{
		tmp = *mem;
		*mem = (*mem)->next;
		free(tmp->ptr);
		free(tmp);
	}
}

void	leaks(void)
{
	system("leak a.out");
}

int main(void)
{
	atexit(leaks);
	t_cmd	*tavern;
	char	**word;

	tavern = my_malloc(sizeof(t_cmd), 0);
	tavern->cmd = my_malloc(sizeof(char *) * 2, 0);
	word = my_malloc(sizeof(char *) * 2, 0);
	// while(1);
	my_malloc(sizeof(char *) * 2, -1);
}
