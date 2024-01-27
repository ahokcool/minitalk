# Makefile for minitalk
.SILENT:

# Variables
NAME_SERVER = server
NAME_CLIENT = client

# Prints DEBUG Messages
DEBUG = 0

# Compiler options
CC = cc
CFLAGS = -D DEBUG=$(DEBUG) -Wall -Werror -Wextra #-g -fsanitize=address -fsanitize-address-use-after-scope
CLIBS = -L$(LIB_FOLDER) -lft -lm
CINCLUDES  = -I$(INCLUDE_FOLDER) 
RM = rm -f

# Color codes
RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m

# ->Folders
SRC_FOLDER = ./src/
INCLUDE_FOLDER = ./include/
LIB_FOLDER = ./lib/
OBJS_FOLDER = ./obj/
TEST_FOLDER = /test/

# ->Files
LIBFT_PRINTF = $(LIB_FOLDER)libft_printf.a
SRCS_SERVER = $(SRC_FOLDER)server.c
SRCS_CLIENT = $(SRC_FOLDER)client.c
	
# Object files
OBJS_SERVER = $(OBJS_FOLDER)server.o
OBJS_CLIENT = $(OBJS_FOLDER)client.o

# TARGETS
.PHONY: all clean fclean re norm test

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(LIBFT_PRINTF) $(OBJS_SERVER)
	$(CC) $(OBJS_SERVER) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME_SERVER)
	echo "$(GREEN)$(NAME_SERVER): created$(RESET)"

$(NAME_CLIENT): $(LIBFT_PRINTF) $(OBJS_CLIENT)
	$(CC) $(OBJS_CLIENT) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME_CLIENT)
	echo "$(GREEN)$(NAME_CLIENT): created$(RESET)"

$(OBJS_SERVER): $(SRC_FOLDER)server.c
	mkdir -p $(OBJS_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_CLIENT): $(SRC_FOLDER)client.c
	mkdir -p $(OBJS_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_PRINTF):
	echo "$(ORANGE)compiling: $(LIBFT_PRINTF)\n$(RESET)"
	$(MAKE) --no-print-directory -C $(LIB_FOLDER) DEBUG=$(DEBUG)

clean:
	$(RM) $(OBJS_SERVER)
	echo "$(RED)$(NAME_SERVER): cleaned object files$(RESET)"
	$(RM) $(OBJS_CLIENT)
	echo "$(RED)$(NAME_CLIENT): cleaned object files$(RESET)"

fclean: clean
	make --no-print-directory -C $(LIB_FOLDER) fclean
	$(RM) $(NAME_SERVER)
	echo "$(RED)$(NAME_SERVER): cleaned program$(RESET)"
	$(RM) $(NAME_CLIENT)
	echo "$(RED)$(NAME_CLIENT): cleaned program$(RESET)"

re: fclean all

test: all
	gnome-terminal --window --hide-menubar --title "ASTEINS MINITALK TESTER" --geometry=60x10+630+100 --working-directory="$(CURDIR)$(TEST_FOLDER)" -- "./run.sh" &

norm:
	norminette
