# Makefile for minitalk

# Variables
NAME = minitalk
NAME_SERVER = server
NAME_CLIENT = client

# Compiler options
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
CLIBS = -L$(LIBFT_FOLDER) -lft -lm
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
LIBFT_FOLDER = $(LIB_FOLDER)libft/
OBJS_FOLDER = ./obj/
TEST_FOLDER = /test/

# ->Files
LIBFT = $(LIBFT_FOLDER)libft.a
BANNER = $(LIBFT_FOLDER)make_banner.sh
SRCS_SERVER = $(SRC_FOLDER)server.c
SRCS_CLIENT = $(SRC_FOLDER)client.c
	
# Object files
OBJS_SERVER = $(OBJS_FOLDER)server.o
OBJS_CLIENT = $(OBJS_FOLDER)client.o

# TARGETS
.PHONY: all clean fclean re norm test

all: MSG_START $(NAME_SERVER) $(NAME_CLIENT) MSG_DONE

$(NAME_SERVER): $(LIBFT) $(OBJS_SERVER)
	@$(CC) $(OBJS_SERVER) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME_SERVER)
	@echo "$(GREEN)$(NAME_SERVER): created$(RESET)"

$(NAME_CLIENT): $(LIBFT) $(OBJS_CLIENT)
	@$(CC) $(OBJS_CLIENT) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME_CLIENT)
	@echo "$(GREEN)$(NAME_CLIENT): created$(RESET)"

$(OBJS_SERVER): $(SRC_FOLDER)server.c
	@mkdir -p $(OBJS_FOLDER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_CLIENT): $(SRC_FOLDER)client.c
	@mkdir -p $(OBJS_FOLDER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_FOLDER)

clean:
	@make --no-print-directory -C $(LIBFT_FOLDER) clean
	@$(RM) $(OBJS_SERVER)
	@$(RM) $(OBJS_CLIENT)
	@$(BANNER) $(NAME) "removed object files" "$(RED)"

fclean: clean
	@make --no-print-directory -C $(LIBFT_FOLDER) fclean
	@$(RM) $(NAME_SERVER)
	@$(RM) $(NAME_CLIENT)
	@$(BANNER) $(NAME) "removed program" "$(RED)"

re: fclean all

test: all
	@gnome-terminal --window --hide-menubar --title "ASTEINS MINITALK TESTER" --geometry=60x10+630+100 --working-directory="$(CURDIR)$(TEST_FOLDER)" -- "./run.sh" &

MSG_START:
	@$(BANNER) $(NAME) compiling "$(ORANGE)"

MSG_DONE:
	@$(BANNER) $(NAME) compiled "$(GREEN)"
