/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 06:55:04 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/21 06:22:08 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_current_directory(void)
{
	char	current_directory[PATH_MAX];

	if (getcwd(current_directory, sizeof(current_directory)) != NULL)
		printf("%s\n", current_directory);
	else 
		error_out("getcwd", 0);
}

int	main(void)
{
	print_current_directory();
}

void	error_out(char *msg, int v)
{
	if (v == 0)
		perror(msg);
	if (v == 1)
		write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

size_t	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
