CC=gcc
BIN_DIR=bin/
OBJ_DIR=obj/
SRC_DIR=src/
INCLUDES=../includes
CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g
CFILES=$(addprefix $(SRC_DIR), ft_abs.c ft_lstmax.c ft_strchr.c ft_atoi.c ft_lstmin.c ft_strcmp.c \
ft_atoll.c ft_lstpop.c ft_strcpy.c ft_bzero.c ft_lstsize.c ft_strdup.c ft_calloc.c  ft_max.c \
ft_striteri.c ft_isalnum.c ft_memchr.c ft_strjoin.c ft_isalpha.c ft_memcmp.c ft_strlcat.c ft_isascii.c \
ft_memcpy.c ft_strlcpy.c ft_isdigit.c ft_memmove.c ft_strlen.c ft_isprint.c ft_memset.c ft_strmapi.c \
ft_iswhitespace.c ft_min.c ft_strncmp.c ft_itoa.c ft_print_addr.c ft_strnstr.c ft_lstadd_back.c \
ft_printf.c ft_strrchr.c ft_lstadd_front.c ft_putchar.c ft_strtrim.c ft_lstclear.c ft_putendl_fd.c \
ft_substr.c ft_lstdelone.c ft_putnbr_base.c ft_swap.c ft_lst_find_at_index.c ft_putnbr.c ft_tolower.c \
ft_lstindex.c ft_putnbr_fd.c ft_toupper.c ft_lstiter.c ft_putstr.c get_next_line.c ft_lstlast.c ft_split.c \
ft_lstnew.c ft_lstsearch.c ft_is_in.c)
OBJS=$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(CFILES))
NAME=$(BIN_DIR)libft.a
HEADER=../includes/libft.h

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -d "./$(OBJ_DIR)" ]; then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
	@if [ ! -d "./$(BIN_DIR)" ]; then mkdir $(dir $@); fi
	ar rc $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean re
