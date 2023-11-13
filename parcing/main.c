/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:11:22 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/13 11:05:53 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_status;

void	print_list(t_tokens *list)
{
	while (list)
	{
		while (list)
		{
			printf("list=%s$\n", list->tokens);
		list = list->next;
		}
		break ;
	}
}

void first_one(t_tokens *list, t_cmd **tmp)
{
	int		n_cmd;

	n_cmd = n_of_cmd(list);
	(*tmp)->cmd = my_malloc((n_cmd + 1), sizeof(char *), 1);
	if (!(*tmp)->cmd)
		return ;
	(*tmp)->cmd[n_cmd] = NULL;
}

void 	parcer(t_tokens *list, t_cmd **f_list, t_env **envr)
{
	t_cmd	*tmp;
	int		flg;
	int		i;

	while (list && list->type != NLINE)
	{
	i = -1;
	add_list(f_list, create_list());
	tmp = ft_lstlast_p(*f_list);
	flg = -1;
		while (list && list->type != NLINE && list->type != PIPE)
		{
			if (!++flg)
				first_one(list, &tmp);
			flg = fill(&list, &tmp, &i, envr);
			if (flg == -1)
			{
				if (g_status == 130)
				{
					f_list = NULL;
					return ;
				}
				while(list->type != PIPE && list->type != NLINE)
					list = list->next;
			}
			else if (!is_token(list->type))
					list = list->next;
		}
		if (list && list->type == PIPE)
		{
			list = list->next;
			if (g_status == 1)
				tmp = tmp->next;
		}
	}
}

void	minishell(t_env **envr, char *b)
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
			break ;
		}
		if (ft_strlen(b))
		{
			add_history(b);
			if ((list = tokenizer(b, envr)) == NULL)
				g_status = 258;
			else if ((g_status = syntax_error(list)) == 258)
				list = NULL;
			f_list = NULL;
			if (list)
				parcer(list, &f_list, envr);
			if (f_list)
				pwd = execute_cmds(&f_list, envr, pwd);
			while (f_list)
			{
				if (f_list && f_list->fd->out != 1)
				{
					close(f_list->fd->out);
					f_list->fd->out = 1;
				}
				if(f_list && f_list->fd->in != 0)
				{
					close(f_list->fd->in);
					f_list->fd->in = 0;
				}
				f_list = f_list->next;
			}
		}
		free(b);
	}
	my_malloc(0, 0, 0);
}

int main(int ac, char **av, char **env)
{
	t_env		*envr;
	char		*b;

	b = NULL;
	g_status = 0;
	(void)ac;
	(void)av;
	g_status = 0;
	if (ac > 1)
	{
		write(2, "minishell: ", 11);
		write(2, av[1], ft_strlen(av[1]));
		write(2, ": No such file or directory\n", 28);
		return (126);
	}
	if (!env || !*env)
        set_env(&envr);
    else
	{
        envr = envirement(env);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	minishell(&envr, b);
	return (0);
}
