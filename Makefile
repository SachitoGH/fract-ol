# Variables

NAME		= fractol
INCLUDE		= include
SRC_DIR		= src
OBJ_DIR		= obj
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I$(INCLUDE)
RM			= rm -rf

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
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	echo "$(GREEN)fract-ol compiled!$(DEFAULT)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	echo "$(YELLOW)Compiling: $<$(DEFAULT)"
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	echo "$(BLUE)fract-ol object files cleaned!$(DEFAULT)"

fclean: clean
	$(RM) $(NAME)
	echo "$(CYAN)fract-ol executable file cleaned!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re
