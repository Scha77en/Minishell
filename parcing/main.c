/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:11:22 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/30 15:06:29 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_cmd *f_list)
{
	int	i;

	i = 0;
	while (f_list)
	{
		while (f_list->cmd[i])
		{
			printf("cmd : %s\n", f_list->cmd[i++]);
		}
		printf("fd_in : %d | fd_out : %d\n", f_list->fd_in, f_list->fd_out);
		printf("-------------\n");
		f_list = f_list->next;
	}
}
void 	parcer(t_tokens *list, t_cmd **f_list)
{
	t_cmd	*tmp;
	int		flg;
	int		n_cmd;
	int		i;

	i = -1;
	add_list(f_list, create_list());
	tmp = ft_lstlast_p(*f_list);
	flg = -1;
	while (list)
	{
		while (list && list->type != NLINE && list->type != PIPE)
		{
			if (!++flg)
			{
				n_cmd = n_of_cmd(list);
				tmp->cmd = malloc(sizeof(char *) * (n_cmd + 1));
				if (!tmp->cmd)
					return ;
				tmp->cmd[n_cmd] = NULL;
			}
			fill(&list, tmp, &i);
			list = list->next;
		}
		list = list->next;
	}
}
void f()
{
	system("leaks minishell");
}

void	free_list(t_tokens **list)
{
	t_tokens	*current;
	t_tokens	*lst;

	lst = *list;
	while (lst)
	{
		current = lst;
		if (current->tokens != NULL)
		{
			printf("f : %s\n", current->tokens);
			// free(current->tokens);
			// free(current);
		}
		lst = lst->next;
	}
}

void	free_f_list(t_cmd **f_list)
{
	t_cmd	*current;
	t_cmd	*lst;
	int		i;

	i = 0;
	lst = *f_list;
	while (lst)
	{
		current = lst;
		lst = lst->next;
		while (current->cmd[i])
			free(current->cmd[i++]);
		free(current->cmd);
		free(current);
	}
}

int main(int ac, char **av, char **env)
{
	t_tokens	*list;
	t_cmd		*f_list;
	t_env		*envr;
	int			exit_status;
	char		*b;

	atexit(f);
	(void)ac;
	(void)av;
	exit_status = 0;
	envr = envirement(env);
	while (1)
	{
		b = readline("minishell$ ");
		if (b == NULL)
			break;
		if (ft_strlen(b))
		{
			add_history(b);
			list = tokenizer(b, &exit_status);
			// while(list)
			// {
			// 	printf("list : -%s- | %d\n", list->tokens, list->type);
			// 	list = list->next;
			// }
			// break ;
			if ((exit_status = syntax_error(list)) == 258)
			{
				free_list(&list);
				list = NULL;
			}
			f_list = NULL;
			if (list)
				parcer(list, &f_list);
			free_list(&list);
			if (f_list != NULL)
			{
				print_list(f_list);
				free_f_list(&f_list);
			}
		}
		free(b);
	}
	return (0);
}
