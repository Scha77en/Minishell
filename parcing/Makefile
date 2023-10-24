NAME = minishell
SRC = main.c tools.c tokenizer.c list.c rederections.c get_next_line.c env.c expand.c tokenizer2.c  \
		../execution/exec.c ../execution/get_next_line_m.c ../execution/get_next_line_utils.c ../execution/spliting.c\
		../execution/joining.c ../execution/path_search.c ../execution/command_search.c\
		../execution/here_doc.c ../execution/redirection_managment.c ../execution/error_handling.c\
		../builtings/cd.c ../builtings/pwd.c ../builtings/unset.c ../builtings/env.c ../builtings/echo.c ../builtings/export_utils.c\
		../builtings/export.c ../builtings/exit.c ../execution/signals.c

READLINE = $(shell brew --prefix readline)

CC = cc

FLGS = -Wall -Wextra -Werror -g -I$(READLINE)/include#-fsanitize=address,undefined

RM = rm -rf

OBJ = $(SRC:%.c=%.o)

all : $(NAME)

%.o : %.c ../includes/minishell.h  
	$(CC) $(FLGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(OBJ) ../libft/libft.a -L$(READLINE)/lib -lreadline -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all