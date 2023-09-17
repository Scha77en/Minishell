NAME = minishell
SRC = main.c tools.c tokenizer.c list.c
CC = cc -g -fsanitize=address
FLGS = -Wall -Wextra -Werror 
RM = rm -rf
OBJ = $(SRC:%.c=%.o)

all : $(NAME)
%.o : %.c msh.h ../libft/libft.h
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