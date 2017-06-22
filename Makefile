NAME	= minishell

SRCS   =	main.c \
			unsentenv.c \
			echo_command.c \
			helper.c \
			run_command.c \
			cd_command.c \
			get_env.c \
			helper_2.c \
			lists_functions.c

HEAD   =	minishell.h

#SRC 	= $(SRCS)
OBJ		= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(OBJ) $(HEAD) -o $(NAME) -L libft/ -lft
	@echo "\033[32mFT_LS: Built minishell. ~(˘▾˘~) \033[0m"

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ)
	@echo "\033[32mFT_LS: Cleaned up object files. ~(˘▾˘~) \033[0m"

fclean: clean
	@$(MAKE) -C ./libft/ fclean
	@rm -rf $(NAME) $(OBJ)

re: fclean $(NAME)