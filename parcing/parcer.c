/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:47:38 by abouregb          #+#    #+#             */
/*   Updated: 2023/11/14 15:37:25 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_syntax(t_tokens *list)
{
	if (is_token(list->type) && list->next->type == NLINE)
		return (0);
	else if (list->type == PIPE \
	&& ((!is_token(list->next->type) && !is_word(list->next->type))
			|| list->next->type == PIPE))
		return (0);
	else if (is_token(list->type) && !is_word(list->next->type)
		&& (list->next->type == WHITESPACE))
		return (0);
	else if (is_token(list->type) 
		&& list->type != PIPE && is_token(list->next->type))
		return (0);
	else
		return (1);
}

void	first_one(t_tokens *list, t_cmd **tmp)
{
	int	n_cmd;

	n_cmd = n_of_cmd(list);
	(*tmp)->cmd = my_malloc((n_cmd + 1), sizeof(char *), 1);
	if (!(*tmp)->cmd)
		return ;
	(*tmp)->cmd[n_cmd] = NULL;
}

void	final_list(t_tokens **list, t_cmd **tmp, int *i, t_env **envr)
{
	int	flg;

	flg = -1;
	while ((*list) && (*list)->type != NLINE && (*list)->type != PIPE)
	{
		if (!++flg)
			first_one((*list), tmp);
		flg = fill(&(*list), tmp, i, envr);
		if (flg == -1)
		{
			while ((*list)->type != PIPE && (*list)->type != NLINE)
				(*list) = (*list)->next;
		}
		else if (!is_token((*list)->type))
			(*list) = (*list)->next;
	}
	if ((*list) && (*list)->type == PIPE)
	{
		(*list) = (*list)->next;
		if (g_status == 1)
			(*tmp) = (*tmp)->next;
	}
}

void	parcer(t_tokens *list, t_cmd **f_list, t_env **envr)
{
	t_cmd	*tmp;
	int		i;

	while (list && list->type != NLINE)
	{
		i = -1;
		add_list(f_list, create_list());
		tmp = ft_lstlast_p(*f_list);
		final_list(&list, &tmp, &i, envr);
	}
}
