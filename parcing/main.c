/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:11:22 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/12 21:52:04 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_status;

void	check_fd(t_cmd **f_list)
{
	while ((*f_list))
	{
		if ((*f_list) && (*f_list)->fd->out != 1)
		{
			close((*f_list)->fd->out);
			(*f_list)->fd->out = 1;
		}
		if ((*f_list) && (*f_list)->fd->in != 0)
		{
			close((*f_list)->fd->in);
			(*f_list)->fd->in = 0;
		}
		(*f_list) = (*f_list)->next;
	}
}

t_cmd	*tokenizer_(char *b, t_env **envr, t_tokens	**list)
{
	add_history(b);
	*list = tokenizer(b, envr);
	if (*list == NULL)
		g_status = 258;
	else if (syntax_error(*list) == 1)
		*list = NULL;
	return (NULL);
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
			tokenizer_(b, envr, &list);
			f_list = NULL;
			parcer(list, &f_list, envr);
			if (f_list)
				pwd = execute_cmds(&f_list, envr, pwd);
			check_fd(&f_list);
		}
		free(b);
	}
	my_malloc(0, 0, 0);
}

int	main(int ac, char **av, char **env)
{
	t_env		*envr;
	char		*b;

	b = NULL;
	g_status = 0;
	(void)ac;
	(void)av;
	g_status = 0;
	if (!env)
		set_env(&envr);
	else
		envr = envirement(env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	minishell(&envr, b);
	return (0);
}
