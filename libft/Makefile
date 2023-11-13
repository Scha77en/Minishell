# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 15:20:44 by aouhbi            #+#    #+#              #
#    Updated: 2023/11/13 15:21:06 by aouhbi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memmove.c ft_memchr.c \
ft_memset.c ft_strlcpy.c ft_strlen.c ft_tolower.c ft_toupper.c ft_strchr.c ft_strlcat.c ft_strrchr.c ft_strncmp.c ft_memcmp.c ft_strnstr.c \
ft_itoa.c ft_calloc.c ft_putnbr_fd.c ft_strdup.c ft_strmapi.c ft_substr.c ft_strjoin.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_strtrim.c ft_striteri.c ft_split.c ft_itoa.c garbage_collector.c\

CC = cc

FLAGS = -Wall -Wextra -Werror -c

OBJS = ${SRCS:.c=.o}

NAME = libft.a

RM = rm -f

all : ${NAME}

${NAME} : ${OBJS}
	ar -rc $@ ${OBJS}

%.o : %.c libft.h
	${CC} ${FLAGS} $<

clean :
	${RM} ${OBJS}
 
fclean : clean
	${RM} ${NAME}

re: fclean all	

.PHONY : all clean fclean re
