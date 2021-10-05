NAME		=	Minishell

HEAD 		=	./includes/*.h

INC			=	-I./includes/ -I/Users/$(USER)/.brew/opt/readline/include

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

INFO		=	echo "Minishell is compiling..." &&

LIBFT_PATH	=	./srcs/Utils/Libft

LIBFT		=	$(LIBFT_PATH)/libft.a

SRCS		= ./srcs/Utils/Common/common_utils.c \
				./srcs/Utils/Common/common_utils2.c \
				./srcs/Utils/Parsing_utils/quote_utils.c \
				./srcs/Utils/Parsing_utils/quote_utils2.c \
				./srcs/Utils/Parsing_utils/parsing_utils.c \
				./srcs/Utils/Parsing_utils/parsing_utils2.c \
				./srcs/Utils/Free/free_utils.c \
				./srcs/Utils/Free/free_utils2.c \
				./srcs/Utils/Write/display.c \
				./srcs/Utils/Write/write_errors.c \
				./srcs/Utils/Write/write_errors2.c \
				./srcs/Utils/Structures/struct_utils.c \
				./srcs/Utils/Variables/variable_utils.c \
				./srcs/Utils/Variables/variable_utils2.c \
				./srcs/Utils/Variables/variable_utils3.c \
				./srcs/Utils/Execution_utils/exec_utils.c \
				./srcs/Parsing/input_process.c \
				./srcs/Parsing/parsing.c \
				./srcs/Execution/cmds.c \
				./srcs/Execution/execution.c \
				./srcs/Execution/execution2.c \
				./srcs/Execution/Pipping_redir/piping.c \
				./srcs/Execution/Pipping_redir/redirection.c \
				./srcs/Execution/Pipping_redir/redirection2.c \
				./srcs/Built_ins/pwd.c \
				./srcs/Built_ins/env.c \
				./srcs/Built_ins/exit.c \
				./srcs/Built_ins/exit2.c \
				./srcs/Built_ins/export.c \
				./srcs/Built_ins/export2.c \
				./srcs/Built_ins/unset.c \
				./srcs/Built_ins/unset2.c \
				./srcs/Built_ins/cd.c \
				./srcs/Built_ins/echo.c \
				./srcs/Built_ins/version.c \
				./srcs/minishell.c \


OBJ			=	$(SRCS:.c=.o)

all: 	$(NAME)

$(OBJ): $(HEAD)

$(NAME): $(OBJ)
	@echo "\033[0;35mLibft is compiling" \
		&& sleep 1  && echo "...\033[0m"
	@cd ./srcs/utils/Libft && make
	@echo "\033[0;32mLibft compilation was succesfull.\033[0m"
	@cd ..
	@echo "\033[0;35mMinishell is compiling" \
		&& sleep 1  && echo "...\033[0m" \
		&& make process

process: $(OBJ)
	@$(CC) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib $(FLAGS) $(INC) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\033[0;32mMinishell compilation was succesfull.\033[0m"

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
