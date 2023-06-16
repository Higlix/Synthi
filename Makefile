

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
RESET = [0m
BOLD = [1m

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
LIB_DIR = lib
RAYLIB_DIR = raylib

RAYLIB = $(RAYLIB_DIR)/src/libraylib.a

LIB += lib/$(RAYLIB)

SRC += $(wildcard $(SRC_DIR)/*.c)

OBJ += $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
#CFLAGS = -Wall -Werror -Wextra -I $(INC_DIR)
CFLAGS = -I $(INC_DIR) -I lib/$(RAYLIB_DIR)/src
NAME = synth

all: $(OBJ_DIR) $(LIB) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@
	@echo "$(MAGENTA)Object directories created..."

$(LIB):
	@make -C lib/$(RAYLIB_DIR)/src

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LIB) -framework IOKit -framework Cocoa -framework OpenGL
	@mkdir -p bin
	@mv $(NAME) bin
	@echo "$(GREEN)Compiled { $(CYAN)$(NAME) $(GREEN)}"

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $< -o $@ $(CFLAGS) 
	@echo "$(GREEN)Compiled {$(RED) $@ $(GREEN)}"

src: clean all

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf bin
	@echo "$(YELLOW)Object directory $(RED)DELETED"

fclean: clean
	@make clean -C lib/$(RAYLIB_DIR)/src
	@echo "$(YELLOW)$(NAME) $(RED)DELETED"

re: fclean all

.PHONY: all clean fclean re