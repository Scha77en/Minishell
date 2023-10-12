/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:11:22 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/29 13:24:16 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     g_status = 0;

t_tokens	*create_node(void)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->tokens = NULL;
	node->next = NULL;
	return (node);
}

void	add_node(t_tokens **list, t_tokens *new)
{
	t_tokens	*tmp;

	if (!(*list))
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		tmp->next->next = NULL;
	}
}

t_tokens	*tokenizer(char *b, t_tokens *list, t_env *env)
{
	int			i;
	t_tokens	*node;

	i = -1;
	while (b[++i])
	{
		node = create_node();
		if ((node->type = token(b[i], ' ')) == WHITESPACE)
		{
			node->tokens = " ";
			while (white_space(b[i + 1]))
				i++;
		}
		else if ((node->type = token(b[i], b[i + 1])) == PIPE)
            node->tokens = "|";
        else if ((node->type = token(b[i], b[i + 1])) == HEREDOC)
        {
            node->tokens = "<<";
            i++;
        }
        else if ((node->type = token(b[i], b[i + 1])) == APPEND)
        {
            node->tokens = ">>";
            i++;
        }
        else if ((node->type = token(b[i], b[i + 1])) == SQUAT)
            node->tokens = fill_token(b, &i, 34);
        else if ((node->type = token(b[i], b[i + 1])) == DQOUT)
            node->tokens = fill_token(b, &i, 39);
        else if ((node->type = token(b[i], b[i + 1])) == OUT)
            node->tokens = ">";
        else if ((node->type = token(b[i], b[i + 1])) == IN)
            node->tokens = "<";
        else
            node->tokens = fill_word(b, &i, env);
        add_node(&list, node);
    }
    node = create_node();
    node->type = NLINE;
    add_node(&list, node);
    return (list);
}

int syntax_error(t_tokens *list)
{
    while(list->next)
    {
        if((is_token(list->type) && !is_word(list->next->type) && list->next->type != WHITESPACE))
            return (printf("syntax error : %s\n", list->tokens), list->type = 0 ,  -1);
        else
            list = list->next;
    }
    return (0);
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_cmd *tmp;
    int n_cmd;
    int flg;
    t_cmd *f_list;
    t_tokens *list;
    t_env *envr;
    char *b;
    static char *pwd;

    if (!env)
        set_env(&envr);
    else
        envr = envirement(env);
    pwd = ft_getenv(&envr, "PWD");
    signal(SIGINT, handle_sigint);
    while(1)
    {
        f_list = NULL;
        list = NULL;
        b = readline("minishell$ ");
        if(b == NULL)
        {
            printf("exit\n");
            exit(0);
        }
         rl_replace_line("", 0);
        if (ft_strlen(b))
            add_history(b);
        list = tokenizer(b, list, envr);
        syntax_error(list);
        while(list)
        {
            add_list(&f_list, create_list());
            tmp = ft_lstlast_p(f_list);
            int i = -1;
            flg = -1;
            while(list && list->type != NLINE && list->type != PIPE)
            {
                if(!++flg)
                {
                    n_cmd = n_of_cmd(list);
                    tmp->cmd = malloc(sizeof(char *) * (n_cmd + 1));
                    tmp->cmd[n_cmd] = NULL;
                }
                fill(&list, tmp, &i);
            }
            tmp = tmp->next;
            list = list->next;
        }
    pwd = execute_cmds(&f_list, env, &envr, pwd);
    }
    return(0);
}
