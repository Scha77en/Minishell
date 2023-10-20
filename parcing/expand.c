/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:45:33 by abouregb          #+#    #+#             */
/*   Updated: 2023/10/20 19:00:17 by abouregb         ###   ########.fr       */
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
    if (!var)
        return (NULL);
    n = 0;
    while(s+1 < *i)
        var[n++] = str[s++];
    if (s < *i)
        var[n++] = str[s++];
    var[n] = '\0';
    return (var);
}
char *check_if_valid_herdoc(char *str, int *i)
{
    int s;
    int n;
    char *var;
    s = (*i);
    n = 0;
    if (str[(*i)] == '?')
    {
        (*i)++;
        n += ft_strlen(ft_itoa(g_status));
    }
    while(str[(*i)] && (ft_isalpha(str[(*i)]) || str[(*i)] == '_'))
    {
        (*i)++;
        n++;
    }
    var = malloc(sizeof(char) * (n +1));
    if (!var)
        return (NULL);
    var[n] = '\0';
    n = 0;
    while(s < *i)
    {
        if (str[s] == '?')
        {
            var = ft_itoa(g_status);
            s++;
            n += ft_strlen(ft_itoa(g_status));
            while(s < *i && str[s] != '?')
                var[n++] = str[s++];
        }//! n9dar nkhdam hnaya b recursion anred had l statemen function 
        else
            var[n++] = str[s++];
    }
    // if (s < *i)
    //     var[n++] = str[s++];
    var = getenv(var);
    return (var);
}
void fill_expand(char *f, int *k, char *value)
{
    if (!ft_isdigit(value[0]))
        value = getenv(value);
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
    if (!r)
    {
        return (NULL);
    }
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
	return (ft_strjoin(r, "\n"));
}

