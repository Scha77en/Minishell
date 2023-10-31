/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:11:22 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/26 18:23:48 by abouregb         ###   ########.fr       */
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
			// printf("cmd : %s\n", f_list->cmd[i++]);
			printf("cmd len %ld \n", ft_strlen(f_list->cmd[i++]));
		}
		// printf("fd_in : %d | fd_out : %d\n", f_list->fd_in, f_list->fd_out);
		printf("-------------\n");
		f_list = f_list->next;
	}
}
void 	parcer(t_tokens *list, t_cmd **f_list, t_env **envr)
{
	t_cmd	*tmp;
	int		flg;
	int		n_cmd;
	int		i;

	while (list->type != NLINE)
	{
	i = -1;
	add_list(f_list, create_list());
	tmp = ft_lstlast_p(*f_list);
	flg = -1;
		while (list && list->type != NLINE && list->type != PIPE)
		{
			if (!++flg)
			{
				n_cmd = n_of_cmd(list);
				tmp->cmd = my_malloc((n_cmd + 1), 1, 1);
				if (!tmp->cmd)
					return ;
			}
			fill(&list, &tmp, &i, envr);
			list = list->next;
		}
		if (list->type == PIPE)
		{
			list = list->next;
			tmp = tmp->next;
		}
	}
}

// void	free_f_list(t_cmd **f_list)
// {
// 	t_cmd	*current;
// 	t_cmd	*lst;
// 	int		i;

// 	lst = *f_list;
// 	while (lst)
// 	{
// 		i = 0;
// 		current = lst;
// 		lst = lst->next;
// 		while (current->cmd[i])
// 			free(current->cmd[i++]);
// 		free(current->cmd);
// 		free(current);
// 	}
// 	*f_list = NULL;
// }

void minishell(t_env **envr, char *b)
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
			if ((list = tokenizer(b, envr)) == NULL)
				g_status = 258;
			else if ((g_status = syntax_error(list)) == 258)
				list = NULL;
			f_list = NULL;
			if (list)
				parcer(list, &f_list, envr);
			if (f_list && f_list->cmd[0] != NULL)
			{
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
	}
}

void	free_env(t_env **envr)
{
	t_env	*current;

	while (*envr)
	{
		current = *envr;
		*envr = (*envr)->next;
		free(current->var);
		free(current->value);
		free(current);
	}
	*envr = NULL;
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
	if (!env)
        set_env(&envr);
    else
	{
        envr = envirement(env);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	minishell(&envr, b);
	free_env(&envr);
	return (0);
}
