NAME = minishell
SRC = parcing/main.c parcing/tools.c parcing/delemeter.c parcing/tokenizer.c parcing/list.c parcing/rederections.c parcing/get_next_line.c parcing/env.c parcing/expand.c parcing/tokenizer2.c  \
		execution/exec.c execution/get_next_line_m.c execution/get_next_line_utils.c execution/spliting.c\
		execution/joining.c execution/path_search.c execution/command_search.c\
		execution/redirection_managment.c execution/error_handling.c\
		builtings/cd.c builtings/pwd.c builtings/unset.c builtings/env.c builtings/echo.c builtings/export_utils.c\
		builtings/export.c builtings/exit.c builtings/export_sort_utils.c execution/signals.c\

SRC_LIB = libft/ft_atoi.c libft/ft_itoa.c libft/ft_putnbr_fd.c libft/ft_strlcpy.c libft/ft_tolower.c\
			libft/ft_bzero.c libft/ft_memchr.c libft/ft_putstr_fd.c libft/ft_strlen.c libft/ft_toupper.c\
			libft/ft_calloc.c libft/ft_memcmp.c libft/ft_split.c libft/ft_strmapi.c libft/garbage_collector.c\
			libft/ft_isalnum.c libft/ft_memcpy.c libft/ft_strchr.c libft/ft_strncmp.c\
			libft/ft_isalpha.c libft/ft_memmove.c libft/ft_strdup.c libft/ft_strnstr.c\
			libft/ft_isascii.c libft/ft_memset.c libft/ft_striteri.c libft/ft_strrchr.c\
			libft/ft_isdigit.c libft/ft_putchar_fd.c libft/ft_strjoin.c libft/ft_strtrim.c\
			libft/ft_isprint.c libft/ft_putendl_fd.c libft/ft_strlcat.c libft/ft_substr.c

READLINE = $(shell brew --prefix readline)

LIBFT = ./libft/libft.a

CC = gcc

FLGS = -Wall -Wextra -Werror -I${READLINE}/include -fsanitize=address -g

RM = rm -rf

OBJ = $(SRC:%.c=%.o)

all : ${LIBFT} $(NAME)


%.o : %.c
	$(CC) $(FLGS) -c $< -o $@

$(NAME) : $(OBJ) includes/minishell.h libft/libft.a
	$(CC) ${FLGS} $(OBJ) -o $@ -L${READLINE}/lib -L./libft -lft -lreadline -lhistory

clean :
	$(RM) $(OBJ)
	make clean -C ./libft

fclean : clean
	$(RM) $(NAME)
	make fclean -C ./libft

${LIBFT} : ${SRC_LIB} libft/libft.h
	make -C libft

re : fclean all
