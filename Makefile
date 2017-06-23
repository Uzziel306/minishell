##=-  Compilatator -=##

NAME = minishell
CC = gcc


##=-  FLAGS -=##

CFLAGS = -Wall -Wextra -g3 #-Werror


##=-  PATH -=##

OBJPATH = obj
SRCPATH = srcs
LIBFT_PATH = libft

INCLUDE_PATH = include/

##=-  Rules -=##

LIBFT = -L $(LIBFT_PATH)
LIBS = $(LIBFT) -lft

INCLUDES = -I./ -I $(LIBFT_PATH)/includes -I $(INCLUDE_PATH)


##=-  Files -=##

OBJ = $(SRC:$(SRCPATH)/%.c=$(OBJPATH)/%.o)
SRC = $(addprefix $(SRCPATH)/,$(SRCSFILES))

SRCSFILES	=	main.c \
			unsetenv.c \
			echo_command.c \
			helper.c \
			run_command.c \
			cd_command.c \
			get_env.c \
			helper_2.c \
			lists_functions.c \
			exit.c

##=-  Process -=##

all: $(NAME)

$(NAME): $(OBJ)
#	@echo "\n\033[33mProcessing\n\033[0m"
	@$(MAKE) -C libft/
	@$(CC) -o $@ $(CFLAGS) $(OBJ) $(LIBS)
#	@echo "\n\033[33mEnd of the Process\n\033[0m"

$(OBJ): $(OBJPATH)/%.o : $(SRCPATH)/%.c
	@mkdir -p $(dir $@)
#	@echo "\033[32m"
	@$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<
#	@echo "\033[0m"

clean:
	@/bin/rm -rf $(OBJPATH)

fclean: clean
	@/bin/rm -rf $(NAME)

re:
	fclean all