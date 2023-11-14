/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:52:26 by aouhbi            #+#    #+#             */
/*   Updated: 2023/11/14 07:28:05 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

// libraries

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <paths.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <dirent.h>

extern int	g_status;

typedef struct s_env
{
	char			*var;
	char			*value;
	int				id;
	struct s_env	*next;
}t_env;

typedef struct s_tokens
{
	char			*tokens;
	int				type;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_fd
{
	int				in;
	int				out;
}	t_fd;

typedef struct s_cmd
{
	char			**cmd;
	struct s_fd		*fd;
	struct s_cmd	*next;
}	t_cmd;

typedef enum e_token
{
	WHITESPACE,
	HEREDOC,
	SQUAT,
	DQOUT,
	OUT,
	APPEND,
	IN,
	WORD,
	PIPE,
	NLINE,
	SLH,
	DEL ,
}	t_token;

typedef struct s_index
{
	int		a;
	int		s;
}	t_index;

// garbage collector

void		*my_malloc(int size, int len, int status);
void		clean_mem(t_mem *head);

// Minishell execution functions

char		*execute_cmds(t_cmd **tavern, t_env **envr, char *pwd);
void		multiple_cmds(t_cmd **tavern, t_env **envr, char **pwd, pid_t pid1);
void		pipes_closing(t_cmd **tavern, int pipfd[2], int *for_next);
void		pipes_handling(t_cmd **tavern, int pipfd[2], int *for_next);
void		execute_command(t_cmd *tavern, t_env **envr);
void		exec_with_path(t_cmd *tavern, char **u_env);
void		handle_sigint(int sig);
char		**update_env(t_env **envr);
char		**env_to_char(t_env **env);
int			path_backslash(char *path);
void		herdoc_sigint(int sig);

void		command_not_found(t_cmd *tavern);
void		no_such_file(t_cmd *tavern);

void		subshell(t_cmd **tavern, t_env **env);
void		execute_shell(t_cmd *tavern, t_env **env);
void		handle_sigquit(int sig);
void		sigint_exec(int sig);
void		waiting_and_signals_handling(int status);
void		fork_failed(void);

// builtings

int			if_builting(t_cmd **tavern, t_env **env, char **pwd);
void		print_working_directory(t_cmd **tavern, char **pwd);
void		redefine_pwd(char **pwd, char *define, t_env **env, int v);
void		ft_add_env_pwd(t_env **env, char *var, char *value);
void		cd_builted(t_cmd **tavern, t_env **env, char **pwd);
void		cd_dash(t_cmd **tavern, t_env **env, char **pwd, char *curwd);
void		cd_path(t_cmd **tavern, t_env **env, char **pwd, char *curwd);
void		oldpwd_update(t_env **env, char *curwd, int v);
void		old_pwd_add(t_env *current, char *cwd);
void		oldpwd_search_update(t_env **env, char *cwd);
t_env		*ft_envnew(char *var, char *value);
void		ft_env(t_cmd **tavern, t_env **env, int v);
void		export_env(t_cmd **tavern, t_env **env, t_env *current);
char		*ft_getenv(t_env **env, char *var);
void		pwd_update(t_env **env);
void		echo_builted(t_cmd *tavern);
int			ft_strncmp_echo(char *s1, char *s2, int n);
void		ft_export(t_cmd *tavern, t_env **env);
char		**split_export(char *split, int *j);
char		*back_slash_parce(char *str, int flag);
int			back_slash(char *str);
int			slash_size(char *str);
void		ft_add_env(t_env **env, char **split, int v, int j);
int			check_validity(char *str, int *v);
int			alpha_undscore(char c);
int			plus_sign(char *str, int v);
void		ft_join_value(t_env **env, char **split);
char		*ft_strndup(char *s, int n);
void		ft_exit(t_cmd *tavern);
void		ft_unset(t_cmd *tavern, t_env **envr);
void		set_env(t_env **env);
void		sort_env(t_env *env);
t_env		*copy_env_list(t_env **env);
void		add_env(t_env **env, char *var, char *value, int v);
void		env_env(t_cmd **tavern, t_env *current);
void		too_much_bro(t_cmd *tavern, int v);
void		swap_env(int v, t_env *current, t_env *front, char *temp);
void		adding_new_env(t_env **env, char **split, int v);
void		manage_the_export(t_cmd *tavern, t_env **env, int v, int i);
void		exit_choice(t_cmd *tavern);
int			ft_isdigit_exit(t_cmd *tavern);
void		erasing_node(t_env **envr, t_env *tmp, t_env *prev);
int			unset_parce(t_cmd *tavern);
int			unvalide_identifier(t_cmd *tavern, int i);

// redirections

void		check_redirections(t_cmd *tavern);
int			writing_data(char *data, int pipfd[2]);
void		here_doc_process(char **data, int pipfd[2], \
			t_tokens *file, t_env *envr);
void		waiting_herdoc_child(t_cmd **tmp, int pipfd[2]);

// joining

char		*ft_strjoin_b(char *s1, char *s2, int v);
char		*ft_strjoin_m(char *s1, char *s2);
void		sign_check(char **ptr, size_t *i, int v);
size_t		ft_strlen_m(char *s);

// spliting

char		**ft_split_m(char *s, char c);

// Minishell functions;

char		**find_path(char **env);
int			get_env_path(char **env);
int			ft_strncmp_m(char *s1, char *s2, int n);
int			command_search(char **path);
int			ft_strcmp(char *s1, char *s2);
void		error_out(char *msg, int v);
t_cmd		*ft_lstlast_p(t_cmd *lst);

// parcing;

// linkedlist of env
void		ft_lstaddback(t_env **hed, t_env *new);
int			white_space(char c);
int			token(char fc, char sc);
void		add_list(t_cmd **list, t_cmd *new);
t_cmd		*create_list(void);
char		*ft_strjoin(char const *s1, char const *s2);
int			is_word(int type);
int			is_token(int type);
int			fill(t_tokens **list, t_cmd **tmp, int *i, t_env **envr);
int			n_of_cmd(t_tokens *list);
int			rederections(t_tokens **list, t_cmd **tmp, t_env **envr);
t_env		*envirement(char **env);
int			syntax_error(t_tokens *list);
char		*fill_var(char *b, int n, int len);
int			cheak(char *b, int *i, int c);
void		add_node(t_tokens **list, t_tokens *new);
char		*fill_word(char *b, int *i, int c, t_env **envr);
t_tokens	*create_node(void);
t_tokens	*tokenizer(char *b, t_env **envr);
void		minishell(t_env **envr, char *b);
char		*fill_delemeter(char *b, int *i, int c);
char		*fill__delemeter(char *b, int s, int a, int *i);
int			is_token_(int c, int q);
int			delemeter(char *b, int i, int o_type);
void		parcer(t_tokens *list, t_cmd **f_list, t_env **envr);
void		first_one(t_tokens *list, t_cmd **tmp);
void		expand(char *b, int *s, int *a, t_env **envr);
void		status(char *b, int *s, int *a, int c);
int			rederect_o_a(t_tokens **t_lst, t_cmd **tmp, t_tokens *current);
int			rederect_in_her(t_tokens **t_lst, t_cmd **tmp, \
			t_tokens *current, t_env **envr);
char		*get_data_r(t_cmd **tmp, t_tokens **file, t_env **envr);
int			print_erorr(t_cmd **tmp, int fd, t_tokens **t_lst);
t_env		*lstnew(void);
int			var_len(char *var);
int			valu_len(char *s, int i);
char		*t_oken(char *str, int *i, char *b, int type);
void		ft_lstaddback(t_env **hed, t_env *new);
int			is_rederections(int type);
void		fill_rederections(t_tokens **node, char *b, int *i);
int			len_of_filled(char *b, int s, int c, t_env **envr);

#endif
