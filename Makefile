NAME = minishell
SRC = parcing/main.c parcing/tools.c parcing/rederect_herdc.c parcing/delemeter.c parcing/more_rederections.c parcing/tokenizer.c parcing/enver.c parcing/parcer.c parcing/list.c parcing/rederections.c parcing/get_next_line.c parcing/env.c parcing/expand.c parcing/tokenizer2.c  \
		execution/exec.c execution/get_next_line_m.c execution/get_next_line_utils.c execution/spliting.c\
		execution/joining.c execution/path_search.c execution/command_search.c\
		execution/redirection_managment.c execution/error_handling.c\
		builtings/cd.c builtings/pwd.c builtings/unset.c builtings/env.c builtings/echo.c builtings/export_utils.c\
		builtings/export.c builtings/exit.c builtings/export_sort_utils.c execution/signals.c\

READLINE = $(shell brew --prefix readline)

LIBFT = ./libft/libft.a

CC = gcc

FLGS = -Wall -Wextra -Werror -I${READLINE}/include -fsanitize=address -g

RM = rm -rf

OBJ = $(SRC:%.c=%.o)

all : ${LIBFT} $(NAME)


%.o : %.c
	$(CC) $(FLGS) -c $< -o $@

$(NAME) : $(OBJ) includes/minishell.h
	$(CC) ${FLGS} $(OBJ) -o $@ -L${READLINE}/lib -L./libft -lft -lreadline -lhistory

clean :
	$(RM) $(OBJ)
	make clean -C ./libft

fclean : clean
	$(RM) $(NAME)
	make fclean -C ./libft

${LIBFT} :
	make -C libft

re : fclean all
