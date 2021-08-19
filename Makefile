NAME		=	Minishell

HEAD 		=	./includes/*.h

INC			=	-I./includes/ -I/Users/$(USER)/.brew/opt/readline/include

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

INFO		=	echo "Minishell is compiling..." &&

LIBFT_PATH	=	./srcs/utils/libft

LIBFT		=	$(LIBFT_PATH)/libft.a

SRCS		= ./srcs/Utils/common_utils.c \
				./srcs/Utils/common_utils2.c \
				./srcs/Utils/common_utils3.c \
				./srcs/Utils/common_utils4.c \
				./srcs/Utils/free_utils.c \
				./srcs/Utils/display.c \
				./srcs/Utils/struct_utils.c \
				./srcs/Utils/write_utils.c \
				./srcs/Utils/variable_utils.c \
				./srcs/Parsing/input_process.c \
				./srcs/minishell.c \
				./srcs/cmds.c \
				./srcs/execution.c \
				./srcs/piping.c \
				./srcs/exit.c \
				./srcs/exec_utils.c \
				./srcs/redirection.c \
				./srcs/Built_ins/pwd.c \
				./srcs/Built_ins/env.c \
				./srcs/Built_ins/export.c \
				./srcs/Built_ins/unset.c \
				./srcs/Built_ins/cd.c \
				./srcs/Built_ins/echo.c \
				./srcs/Built_ins/version.c \
				./srcs/Parsing/parsing.c


OBJ			=	$(SRCS:.c=.o)

all: 	$(NAME)

$(OBJ): $(HEAD)

$(NAME): $(OBJ)
	@echo "\033[0;35mLibft is compiling" \
		&& sleep 1  && echo "...\033[0m"
	@cd ./srcs/utils/libft && make
	@echo "\033[0;32mLibft compilation was succesfull.\033[0m"
	@cd ..
	@echo "\033[0;35mMinishell is compiling" \
		&& sleep 1  && echo "...\033[0m" \
		&& make process

process: $(OBJ)
	@$(CC) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib $(FLAGS) $(INC) -o $(NAME) $(OBJ) $(LIBFT)
	@make clean && echo "\033[0;32mMinishell compilation was succesfull.\033[0m"

%.o: %.c
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
	make -C $(LIBFT_PATH) $@
	rm -f $(OBJ)
	@echo "\033[0;31mMinishell object files deletion complete\033[0m"

test:
	valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=no ./$(NAME)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "\033[0;31mLibft objects files deletion complete\033[0m"

re:
	@make clean
	@make process

.PHONY: all clean fclean re
