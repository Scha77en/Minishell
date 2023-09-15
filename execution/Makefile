SRC = main.c get_next_line.c get_next_line_utils.c spliting.c joining.c path_search.c\
		command_search.c linked_tools.c

INCL = ../includes/minishell.h

FLAGS = -Wall -Wextra -Werror

NAME = Minishell

RM = rm -rf

all : ${NAME}

${NAME} : ${SRC} ${INCL}
		cc ${SRC} -o $@

clean :
	@echo All clean

fclean :
	${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re
