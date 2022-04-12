CC=gcc
BIN_DIR=bin/
OBJ_DIR=obj/
SRC_DIR=src/
INCLUDES=includes/
CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES)
NAME=$(BIN_DIR)minishell

CFILES=$(addprefix $(SRC_DIR), main.c token.c utils.c builtins/exit.c)
OBJS=$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(CFILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -lreadline -o $@

$(NAME): $(OBJS)
	@if [ ! -d "./$(BIN_DIR)" ]; then mkdir $(dir $@); fi
	$(MAKE) -C libft/
	$(CC) $(CFLAGS) $(OBJS) libft/bin/libft.a -lreadline -o $(NAME)

all: $(NAME)

debug: CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g
debug: $(NAME)

debug_sanitize:CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g -fsanitize=address
debug_sanitize: $(NAME)

clean:
	$(MAKE) clean -C libft/
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf libft/bin/libft.a
	rm -rf $(BIN_DIR)

sanitize:CFLAGS=-lreadline -Wall -Wextra -Werror -I $(INCLUDES) -fsanitize=address
sanitize: $(NAME)

re: fclean all

re_debug: fclean debug

re_sanitize: fclean sanitize

re_debug_sanitize: fclean debug_sanitize

.PHONY: all debug clean fclean sanitize \
re re_debug re_sanitize re_debug_sanitize
