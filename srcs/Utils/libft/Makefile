# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/18 12:51:25 by alganoun          #+#    #+#              #
#    Updated: 2021/08/22 03:57:28 by allanganoun      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= libft.a

HEAD	= ./libft.h

SRCS	= ./ft_atoi.c ./ft_bzero.c \
			./ft_calloc.c ./ft_isalnum.c \
			./ft_isalpha.c ./ft_isascii.c \
			./ft_isdigit.c ./ft_isprint.c ./ft_itoa.c \
			./ft_memccpy.c ./ft_memchr.c \
			./ft_memcmp.c ./ft_memcpy.c \
			./ft_memmove.c ./ft_memset.c \
			./ft_putchar_fd.c ./ft_putendl_fd.c \
			./ft_putnbr_fd.c ./ft_putstr_fd.c \
			./ft_split.c ./ft_strchr.c ./ft_strcpy.c \
			./ft_strdup.c ./ft_strjoin.c \
			./ft_strlcat.c ./ft_strlcpy.c \
			./ft_strlen.c ./ft_strmapi.c \
			./ft_strncmp.c ./ft_strnstr.c ./ft_strstr.c \
			./ft_strcmp.c ./ft_strrchr.c ./ft_strtrim.c \
			./ft_substr.c ./ft_tolower.c \
			./ft_toupper.c \
			./ft_rm_whitespace.c \
			./ft_malloc.c ./ft_tablen.c \
			./ft_tabdup.c \
			./get_next_line.c


BONUS	= ./ft_lstadd_front_bonus.c ./ft_lstnew_bonus.c \
			./ft_lstsize_bonus.c ./ft_lstlast_bonus.c \
			./ft_lstadd_back_bonus.c ./ft_lstmap_bonus.c \
			./ft_lstiter_bonus.c ./ft_lstdelone_bonus.c \
			./ft_lstclear_bonus.c

OBJS	= ${SRCS:.c=.o}

OBJBNUS = ${BONUS:.c=.o}

CC 		= gcc -Wall -Wextra -Werror

RM		= rm -f

all: ${NAME}

$(OBJS) : ${HEAD}

$(OBJBNUS) : ${OBJ} ${HEAD}

$(NAME): ${OBJS}
		ar rc ${NAME} ${OBJS}

bonus: ${OBJBNUS} ${OBJS}
		ar rc ${NAME} ${OBJS} ${OBJBNUS}

clean:
		${RM} ${OBJS} ${OBJBNUS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
