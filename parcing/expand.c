/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:45:33 by abouregb          #+#    #+#             */
/*   Updated: 2023/09/26 11:38:55 by abouregb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int find_exp(char *s)
{
    int i;

    i = 0;
    while(s[i])
    {
        if(s[i] == '$')
            return(i+1);
        else if (s[i] == 39 || s[i] == 34)
            return (0);
        i++;
    }
    return(0);
}
char *compare(char *var, t_env *env)
{
    while(env)
    {
        if(ft_strncmp(var, env->var, ft_strlen(var)) == 0)
        {
            if(!env->var[ft_strlen(var)])
                return (env->value);
        }
        env = env->next;       
    }
    return (NULL);
}
char *check_if_valid(char *str, int *i)
{
    int s;
    int n;
    char *var;
    s = (*i);
    n = 0;
    while(str[(*i)] && (ft_isalpha(str[(*i)]) || str[(*i)] == '_'))
    {
        (*i)++;
        n++;
    }
    var = malloc(sizeof(char) * (n +1));
    n = 0;
    while(s+1 < *i)
        var[n++] = str[s++];
    if (s < *i)
        var[n++] = str[s++];
    var[n] = '\0';
    var = getenv(var);
    return (var);
}
void fill_expand(char *f, int *k, char *value)
{
    int i;

    i = 0;
    while(value[i])
        f[(*k)++] = value[i++];
}
char *update_line(char *line, char *var, int l)
{
	char *r;
	int i;
	int k;

	i = 0;
	k = 0;
	l = ft_strlen(var) + l;
	r = malloc(sizeof(char) * (l + 1));
	r[l] = '\0';
	while(i < l)
	{
		if (line[i] == '$')
            while(var[k])
			    r[i++] = var[k++];
		else
		{
			r[i] = line[i];
			i++;
		}
	}
	return (r);
}

