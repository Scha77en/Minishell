/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:52:26 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/15 18:36:26 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

# include <paths.h>

// libraries

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

typedef struct s_tokens
{
	char			*tokens;
	int				type;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_red
{
	int				type;
	char			*file;
	struct s_red	*next;
}	t_red;

typedef struct s_cmd
{
	char			*cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_final_list
{
	t_cmd				*cmds;
	t_red				*rederections;
	struct s_final_list	*next;
}	t_final_list;

typedef enum e_token
{
	WHITESPACE, // " "
	HEREDOC,  // <<
	SQUAT,      // '
	DQOUT,       // "
	OUT,      // >
	APPEND,   // >>
	IN,       // <
	WORD,      // string
	PIPE,     // |
	NLINE,     // |
}	t_token;

// get_next_line() structure;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

// get_next_line() functions;

char	*get_next_line(int fd);
void	read_and_save(int fd, t_list **head);
char	*get_the_line(t_list *head);
void	modify_list(t_list **head);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *content, ssize_t readed);
int		ft_lstchr(t_list *head, char *s, int v);
char	*allocate_to_line(t_list *stash);
void	ft_lstclear(t_list *lst);
char	*get_data(char **argv);

// a struct to save the parsing arguments;

typedef struct s_data_nodes
{
	char				*cmd;
	int					type;
	int					id_node;
	struct s_data_nodes	*next;
	struct s_data_nodes	*previous;
}	t_data;

typedef struct s_num
{
	int		collection;
}	t_n;

// Minishell functions;

void	manage_commands(t_data *data, int *pipfd, char **env);
void	manage_first_cmd(t_data *current, int *pipfd, char **env);
void	manage_inbetween_cmd(t_data *current, int *pipfd, char **env);
void	manage_last_cmd(t_data *current, int *pipfd, char **env);
char	**ft_split(char *s, char c);
char	**find_path(char **env);
int		get_env_path(char **env);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin_b(char *s1, char *s2, int v);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
int		command_search(char **path);
int		ft_strcmp(char *s1, char *s2);
void	error_out(char *msg, int v);
void	type_specifier(t_data **data, char *cmd);
void	store_cmd_in_nodes(t_data **data, char **ptr);
t_data	*ft_lstnew_m(char *content, int v);
void	ft_lstadd_back_m(t_data **lst, t_data *new);
t_data	*ft_lstlast_m(t_data *lst);
void	*free_mem(char **ptr, int j);

#endif

// it will be improved with time and what we would need;