NAME = Minishell
SRC = main.c tools.c tokenizer.c list.c rederections.c get_next_line.c env.c expand.c\
		../execution/main.c ../execution/get_next_line_m.c ../execution/get_next_line_utils.c ../execution/spliting.c\
		../execution/joining.c ../execution/path_search.c ../execution/command_search.c ../execution/linked_tools.c\
		../execution/here_doc.c ../execution/redirection_managment.c ../execution/error_handling.c
CC = cc -g -fsanitize=address
FLGS = -Wall -Wextra -Werror 
RM = rm -rf
OBJ = $(SRC:%.c=%.o)

all : $(NAME)
%.o : %.c ../includes/minishell.h ../libft/libft.h cd ../get_next_line && make clean
	$(CC) $(FLGS)  -c $< -o $@

$(NAME) : $(OBJ)
	cd ../libft && make
	$(CC) $(FLGS) $(OBJ) ../libft/libft.a -lreadline -o $(NAME)

clean :
	cd ../libft && make clean
	$(RM) $(OBJ)

fclean : clean
	cd ../libft && make fclean
	$(RM) $(NAME)

re : fclean all