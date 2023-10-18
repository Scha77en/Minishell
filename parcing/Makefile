NAME = Minishell
SRC = main.c tools.c tokenizer.c list.c _fill_token.c rederections.c get_next_line.c env.c expand.c tokenizer2.c fill_token.c \
		../execution/main.c ../execution/get_next_line_m.c ../execution/get_next_line_utils.c ../execution/spliting.c\
		../execution/joining.c ../execution/path_search.c ../execution/command_search.c ../execution/linked_tools.c\
		../execution/here_doc.c ../execution/redirection_managment.c ../execution/error_handling.c ../execution/check.c
CC = cc 
FLGS =  -g #-fsanitize=address,undefined
RM = rm -rf
OBJ = $(SRC:%.c=%.o)

all : $(NAME)

%.o : %.c ../includes/minishell.h
	$(CC) $(FLGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(OBJ) ../libft/libft.a -lreadline -o $@
clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all