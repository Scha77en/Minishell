#include "../includes/minishell.h"

t_env	*copy_node(t_env *node)
{
    t_env *temp;

	temp = (t_env*)malloc(sizeof(t_env));
    temp->var = strdup(node->var);
    temp->value = strdup(node->value);
    temp->id = node->id;
    temp->next = NULL;
    return (temp);
}

t_env	*copy_list(t_env *head)
{

    t_env *head_copy;
    t_env *ptr;

    if (head == NULL)
	{
        return (NULL);
	}
	head_copy = copy_node(head);
	ptr = head_copy;
    while (head->next != NULL)
    {
        head = head->next;
        ptr->next = copy_node(head);
        ptr = ptr->next;
    }

    return (head_copy);
}

t_env	*export_sort(t_env *head_ref)
{
	t_env		*head_copy;
    int			swapped;
    t_env		*ptr1;
    t_env		*ptr2 = NULL;
    t_env		*lptr = NULL;

	head_copy = copy_list(head_ref);
    if (head_copy == NULL)
	{
        return (NULL);
	}
	swapped = 1;
    while (swapped)
    {
        swapped = 0;
        ptr1 = head_copy;
        while (ptr1->next != lptr)
        {
            ptr2 = ptr1->next;
            if (strcmp(ptr1->var, ptr2->var) > 0)
            {
                swap(ptr1, ptr2);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
	return (lptr);
}
