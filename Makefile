NAME = minishell
CC = gcc
LIBFT_DIR=libft/
LIBFT_NAME=libft.a
LIBFT  = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

SRC_PATH = src/

PARSING_DIR=parsing/
PARSING=$(addprefix $(SRC_PATH), $(PARSING_DIR))

EXE_DIR=executor/
EXECUTOR=$(addprefix $(SRC_PATH), $(EXE_DIR))

CFLAGS = -Wall -Werror -Wextra -lreadline -g
SRCS = minishell.c $(PARSING)parsing.c $(PARSING)str_to_struct.c \
		$(PARSING)input_to_str.c $(SRC_PATH)struct_utils.c $(SRC_PATH)utils.c \
		$(EXECUTOR)pipes_redir.c $(EXECUTOR)executor.c
OBJS = $(SRCS:.c=.o)
UNAME_S := $(shell uname -s)

all: check_os $(NAME)

check_os:
ifeq ($(UNAME_S),Darwin)
CFLAGS = -Wall -Werror -Wextra -lreadline -L /opt/homebrew/Cellar/readline/8.1.2/lib -I /opt/homebrew/Cellar/readline/8.1.2/include
endif

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): lib $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(CFLAGS)

lib:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@rm -f .*.swp
	@rm -f */.*.swp
	@rm -f a.out
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)$(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
