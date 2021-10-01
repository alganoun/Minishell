# Colors
GREY = \033[4;34m
RED = \033[1;31m
GREEN = \033[3;32m
YELLOW = \033[2;49;33m
BLUE = \033[4;34m
BLUEE = \033[3;34m
PURPLE = \033[3;35m
CYAN = \033[3;36m
RESET = \033[0m
ICONOK = \033[1;32m
ICONKO = \033[1;31m
CO_DELET = \033[3;31m
CO_A_OUT = \033[96m
WHITE = \033[1;49;97m

NAME = libft.a

HEADER = ./Includes

CC = gcc

L = srcs/

SRCS =	$(L)ft_utils.c \
		$(L)ft_utils2.c \
		$(L)atoi_numb.c \
		$(L)ft_isalnum.c \
		$(L)ft_isalpha.c \
		$(L)ft_isascii.c \
		$(L)ft_isdigit.c \
		$(L)ft_isprint.c \
		$(L)ft_tolower.c \
		$(L)ft_toupper.c \
		$(L)ft_bzero.c \
		$(L)ft_memchr.c \
		$(L)ft_memcpy.c \
		$(L)ft_memmove.c \
		$(L)ft_memset.c \
		$(L)ft_memcmp.c \
		$(L)ft_calloc.c \
		$(L)ft_strdup.c \
		$(L)ft_strlcat.c \
		$(L)ft_strcpy.c \
		$(L)ft_strlcpy.c \
		$(L)ft_strlen.c \
		$(L)ft_strstr.c \
		$(L)ft_strnstr.c \
		$(L)ft_strrchr.c \
		$(L)ft_strchr.c \
		$(L)ft_strncmp.c \
		$(L)ft_atoi.c \
		$(L)ft_substr.c \
		$(L)ft_strjoin.c \
		$(L)ft_strtrim.c \
		$(L)ft_split.c \
		$(L)ft_itoa.c \
		$(L)ft_strmapi.c \
		$(L)ft_putchar_fd.c \
		$(L)ft_putchar_fd.c \
		$(L)ft_putendl_fd.c \
		$(L)ft_putnbr_fd.c \
		$(L)ft_putstr_fd.c \
		$(L)ft_memccpy.c \
		$(L)ft_lstnew.c \
		$(L)ft_lstadd_front.c \
		$(L)ft_lstsize.c \
		$(L)ft_lstlast.c \
		$(L)ft_lstadd_back.c \
		$(L)ft_lstdelone.c \
		$(L)ft_lstclear.c \
		$(L)ft_lstiter.c \
		$(L)ft_lstmap.c \
		$(L)get_next_line.c \
		$(L)ft_malloc.c \
		$(L)ft_tabdup.c \
		$(L)ft_tablen.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all:	$(NAME)

%.o: %.c $(HEADER)
			@printf "\033[2K\r$(PURPLE)$<: $(CYAN)loading..$(RESET)"
			@gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
		@ar rcs $(NAME) $(OBJS)
		@printf "\033[2K\r$(BLUE)$(NAME)$(RESET)$(BLUEE): $(ICONOK)Success [√]$(RESET)\n"

clean:
		@$(RM) $(OBJS)

fclean:
		@$(RM) $(OBJS)
		@$(RM) $(NAME)

re : fclean all

help :
		@printf "\n$(GREY)Welcome to my Makefile.$(RESET)\n\n"
		@printf "$(YELLOW)all              $(RESET)$(WHITE) - run compilation of libftprintf.a  \n\n"
		@printf "$(YELLOW)clean            $(RESET)$(WHITE) - delete all .o (OBJS) \n\n"
		@printf "$(YELLOW)fclean           $(RESET)$(WHITE) - delete all .o (OBJS) and libftprintf.a \n\n"
		@printf "$(YELLOW)re               $(RESET)$(WHITE) - do fclean and all\n\n"

.PHONY: all clean fclean re help
