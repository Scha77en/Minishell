/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouregb <abouregb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:52:26 by aouhbi            #+#    #+#             */
/*   Updated: 2023/09/30 13:22:14 by abouregb         ###   ########.fr       */
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
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_tokens
{
	char			*tokens;
	int				type;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_cmd
{
	char			**cmd;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

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

char	*get_next_line_m(int fd);
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

// Minishell execution testing functions

t_cmd	*ft_lstnew_t(char **content, int fd_in, int fd_out);
t_cmd	*ft_lstlast_t(t_cmd *lst);
void	ft_lstadd_back_t(t_cmd **lst, t_cmd *new);
void	execute_cmds(t_cmd *tavern, char **env);
void	execute_command(t_cmd *tavern, int *pipfd, char **env);
void	manage_first_child(t_cmd *cmds, int *pipfd, char **env);
void	command_handler(t_cmd *tavern, int *pipfd, char **env);
void	manage_children(t_cmd *cmds, int *pipfd, char **env);
void	manage_last_child(t_cmd *cmds, int *pipfd, char **env);
void	single_cmd_exec(t_cmd *tavern, char **env);
char	*ft_strdup_m(char *s1);
void	*ft_memcpy_m(void *dst, void *src, size_t n);

// here_document

void	here_doc_management(t_cmd *tavern, int *pipfd, char **env);
char	*get_data_hr(t_cmd *tavern);
int		ft_strcmp_herdoc(char *s1, char *s2);
void	here_doc_cmd(t_cmd *tavern, int *pipfd, char **env, char *data);
int		writing_data(char *data);
char	*generate_file(void);
void	waiting_und_closing(pid_t pid1, pid_t pid2, int *pipfd);

// other redirections

void	manage_redirection(t_cmd *tavern, int *pipfd, char **env);
void	handle_input(t_cmd *tavern, int *pipfd, char **env);
void	handle_output(t_cmd *tavern, int *pipfd, char **env);
void	handle_append(t_cmd *tavern, int *pipfd, char **env);

// joining

char	*ft_strjoin_b(char *s1, char *s2, int v);
char	*ft_strjoin_m(char *s1, char *s2);
size_t	ft_strlen_m(char *s);

// spliting

void	*free_mem(char **ptr, int j);
char	**ft_split_m(char *s, char c);

// Minishell functions;

void	manage_commands(t_data *data, int *pipfd, char **env);
void	manage_first_cmd(t_data *current, int *pipfd, char **env);
void	manage_inbetween_cmd(t_data *current, int *pipfd, char **env);
void	manage_last_cmd(t_data *current, int *pipfd, char **env);
char	**ft_split_m(char *s, char c);
char	**find_path(char **env);
int		get_env_path(char **env);
int		ft_strncmp_m(char *s1, char *s2, int n);
char	*ft_strjoin_b(char *s1, char *s2, int v);
char	*ft_strjoin_m(char *s1, char *s2);
size_t	ft_strlen_m(char *s);
int		command_search(char **path);
int		ft_strcmp(char *s1, char *s2);
void	error_out(char *msg, int v);
void	type_specifier(t_data **data, char *cmd);
void	store_cmd_in_nodes(t_data **data, char **ptr);
t_cmd	*ft_lstnew_m(char *content);
void	ft_lstadd_back_m(t_data **lst, t_data *new);
t_data	*ft_lstlast_m(t_data *lst);
t_cmd	*ft_lstlast_p(t_cmd *lst);
void	*free_mem(char **ptr, int j);

// parcing;

//get_next_line
char	*get_next_line(int fd);
// linkedlist of env
void	ft_lstaddback(t_env **hed, t_env *new);
t_env	*lstnew(void);
int		white_space(char c);
int		token(char fc, char sc);
void	add_list(t_cmd **list, t_cmd *new);
t_cmd	*create_list(void);
char	*ft_strjoin(char const *s1, char const *s2);
int		is_word(int type);
int		is_token(int type);
void	fill(t_tokens **list, t_cmd *tmp, int *i);
int		n_of_cmd(t_tokens *list);
void	rederections(t_tokens **list, t_cmd *tmp);
t_env	*envirement(char **env);
int		find_exp(char *s);
char	*check_if_valid(char *str, int *i);
void	fill_expand(char *f, int *k, char *env);
int		syntax_error(t_tokens *list);
char	*fill_var(char *b, int n, int len);
char	*update_line(char *line, char *var, int l);
int		cheak(char *b, int *i, int c);
void	add_node(t_tokens **list, t_tokens *new);
char	*check_if_valid_herdoc(char *str, int *i);
char	*fill_word(char *b, int *i, int *exit_status);
char	*fill_token(char *b, int *i, char c, int *exit_status);
t_tokens	*create_node(void);
t_tokens	*tokenizer(char *b, int *exit_status);
#endif

// it will be improved with time and what we would need;