#include "../includes/minishell.h"

t_env   *copy_env_list(t_env **env)
{
    t_env   *head;
	t_env   *curr;

	head = NULL;
	curr = *env;
	while (curr)
	{
        add_env(&head, curr->var, curr->value, curr->id);
		curr = curr->next;
	}
	return (head);
}

void    sort_env(t_env *env)
{
    t_env	*current;
	t_env	*front;
	char	*temp;
    int     v;

	current = env;
	while (current)
	{
		front = current->next;
		while (front)
		{
			if (ft_strcmp(current->var, front->var) > 0)
			{
				temp = current->var;
				current->var = front->var;
				front->var = temp;
                temp = current->value;
                current->value = front->value;
                front->value = temp;
                v = current->id;
                current->id = front->id;
                front->id = v;
			}
			front = front->next;
		}
		current = current->next;
	}
}

void    add_env(t_env **env, char *var, char *value, int v)
{
    t_env   *new;
    t_env   *current;

    new = malloc(sizeof(t_env));
    new->var = ft_strdup(var);
    new->value = ft_strdup(value);
    new->id = v;
    new->next = NULL;
    if (!(*env))
        *env = new;
    else
    {
        current = *env;
        while (current->next)
            current = current->next;
        current->next = new;
    }
}