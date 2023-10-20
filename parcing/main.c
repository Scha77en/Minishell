/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:11:22 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/18 08:02:47 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_status;

void	print_list(t_cmd *f_list)
{
	int	i;

	while (f_list)
	{
		i = 0;
		while (f_list->cmd[i])
		{
			printf("cmd : %s\n", f_list->cmd[i++]);
		}
		// printf("fd_in : %d | fd_out : %d\n", f_list->fd_in, f_list->fd_out);
		printf("-------------\n");
		f_list = f_list->next;
	}
}
void 	parcer(t_tokens *list, t_cmd **f_list, t_fd **fd)
{
	t_cmd	*tmp;
	int		flg;
	int		n_cmd;
	int		i;

	while (list->type != NLINE)
	{
	i = -1;
	add_list(f_list, create_list());
	(*f_list)->fd = *fd;
	tmp = ft_lstlast_p(*f_list);
	flg = -1;
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
			fill(&list, &tmp, &i);
			list = list->next;
		}
		if (list->type == PIPE)
		{
			list = list->next;
			tmp = tmp->next;
		}
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
			free(current);
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
void minishell(char **env, t_env **envr, char *b, t_fd **fd)
{
	t_tokens	*list;
	t_cmd		*f_list;
	static char	*pwd;

	pwd = ft_getenv(envr, "PWD");
	while (1)
	{
		b = readline("minishell$ ");
		if (b == NULL)
		{
			printf("exit\n");
			break;
		}
		if (ft_strlen(b))
		{
			add_history(b);
			list = tokenizer(b);
			if ((g_status = syntax_error(list)) == 258)
			{
				free_list(&list);
				list = NULL;
			}
			f_list = NULL;
			if (list)
				parcer(list, &f_list, fd);//?hna katbaddal list ba9i maareftch 3lach....?
			if (f_list->cmd[0] != NULL)
				pwd = execute_cmds(&f_list, env, envr, pwd);
			// free_list(&list);
			// if (f_list != NULL)
			// {
			// 	print_list(f_list);
			// 	free_f_list(&f_list);
			// }
		}
	}
}

int main(int ac, char **av, char **env)
{
	t_fd		*fd;
	t_env		*envr;
	char		*b;

	// atexit(f);
	b = NULL;
	g_status = 0;
	(void)ac;
	(void)av;
	g_status = 0;
	fd = malloc(sizeof(t_fd));
	fd->in = 0;
	fd->out = 1;
	if (!env)
        set_env(&envr);
    else
	{
        envr = envirement(env);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	minishell(env, &envr, b, &fd);
	return (0);
}
