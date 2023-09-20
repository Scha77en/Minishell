#include "msh.h"


t_env	*lstnew()
{
	t_env	*link;

	if (!(link = malloc(sizeof(t_env))))
		return (NULL);
	link->next = NULL;
	return (link);
}

void	ft_lstaddback(t_env **hed, t_env *new)
{
	t_env *ptr;

	if (*hed)
	{
        printf("one\n");
		ptr = *hed;
		while (ptr)
			ptr = ptr->next;
		ptr = new;
	}
	else if (!*hed)
		*hed = new;
}

int var_len(char *var)
{
    int i = 0;
    while(var[i] != '=')
        i++;
    return (i);
}
int valu_len(char *s, int i)
{
    int r;

    r = 0;
    while(s[i++])
        r++;
    return (r);
}
int main(int ac, char **av, char **env)
{
    int i;
    int s;
    int n = -1;
    i = 0;
    t_env *nv;
    nv = NULL;
    t_env *head;
    (void)ac;
    (void)av;
    
    while(env[++n]) 
    {
        ft_lstaddback(&nv, lstnew());
        if(!i)
            head = nv;
        else
            nv = nv->next;
        i = -1;
        nv->var = malloc(sizeof(char) * (var_len(env[n]) + 1));
        nv->var[var_len(env[n])] = '\0';
        while(env[n][++i] != '=')
            nv->var[i] = env[n][i];
        s = i + 1;
        i = -1;
        nv->value = malloc(sizeof(char) * (valu_len(env[n], s) + 1));
        nv->value[valu_len(env[n], s)] = '\0';
        while(env[n][++i])
            nv->value[i] = env[n][s++];
    }
}