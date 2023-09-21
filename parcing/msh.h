#ifndef MSH_H
#define MSH_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <fcntl.h>

typedef struct s_tokens
{
	char *tokens;
	int type;
	struct s_tokens *next;
}t_tokens;

typedef struct s_cmd
{
	char 	**cmd;
	int		fd_in;
	int		fd_out;
	struct s_cmd *next;
}t_cmd;

typedef struct s_env
{
	char *var;
	char *value;
	struct s_env *next;
}t_env;


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
}t_token;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//get_next_line
char	*get_next_line(int fd);
// linkedlist of env
void			ft_lstaddback(t_env **hed, t_env *new);
t_env			*lstnew();
///
int				white_space(char c);
char *fill_word(char *b, int *i, t_env *env);
int				token(char fc, char sc);
char			*fill_token(char *b, int *i, char c);
void			add_list(t_cmd **list, t_cmd *new);
t_cmd			*create_list();
char			*ft_strjoin(char const *s1, char const *s2);
int				is_word(int type);
int				is_token(int type);
void			fill(t_tokens **list, t_cmd *tmp, int *i);
int				n_of_cmd(t_tokens *list);
void			rederections(t_tokens **list, t_cmd *tmp);
t_env 			*envirement(char **env);
int				find_exp(char *s, int *i, char c);
char *check_if_valid(char *str, int *i ,t_env *env);
void 			fill_expand(char **f, int *k, char *env);

#endif