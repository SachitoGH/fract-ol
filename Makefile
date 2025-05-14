# Variables

NAME		= fractol
INCLUDE 	= -Iinclude -Imlx
SRC_DIR		= src
OBJ_DIR		= obj
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -rf
LIBS = -Lmlx -lmlx -lXext -lX11 -lm -lbsd


# Colors

DEFAULT	= \033[0;39m
GRAY	= \033[0;90m
RED		= \033[0;91m
GREEN	= \033[0;92m
YELLOW	= \033[0;93m
BLUE	= \033[0;94m
MAGENTA	= \033[0;95m
CYAN	= \033[0;96m
WHITE	= \033[0;97m

# Sources

SRC_FILES	=	main \
				event \
				image \
				utils

SRC 	= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ 	= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

# Targets

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	echo "$(YELLOW)Creating $(NAME)$(DEFAULT)"
	$(CC) $(OBJ) $(LIBS) -o $(NAME)
	echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	echo "$(YELLOW)Compiling: $<$(DEFAULT)"
	mkdir -p $(@D)
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	echo "$(BLUE)fract-ol object file cleaned!$(DEFAULT)"

fclean: clean
	$(RM) $(NAME)
	echo "$(CYAN)fract-ol executable file cleaned!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re
