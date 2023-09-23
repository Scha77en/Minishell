#ifndef MSH_H
# define MSH_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../includes/minishell.h"
# include "../libft/libft.h"
# include <fcntl.h>

// typedef struct s_tokens
// {
// 	char *tokens;
// 	int type;
// 	struct s_tokens *next;
// }t_tokens;

// typedef struct s_cmd
// {
// 	char 	**cmd;
// 	int		fd_in;
// 	int		fd_out;
// 	struct s_cmd *next;
// }t_cmd;

// typedef struct s_env
// {
// 	char *var;
// 	char *value;
// 	struct s_env *next;
// }t_env;


// typedef enum e_token
// {
// 	WHITESPACE, // " "
// 	HEREDOC,  // <<
// 	SQUAT,      // '
// 	DQOUT,       // "
// 	OUT,      // >
// 	APPEND,   // >>
// 	IN,       // <
// 	WORD,      // string
// 	PIPE,     // |
// 	NLINE,     // |
// }t_token;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif