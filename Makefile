NAME = minishell
CC = gcc
LIBFT_PATH=libft/
LIBFT_NAME=libft.a
LIBFT  = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))
SRC_PATH = src/
CFLAGS = -Wall -Werror -Wextra -lreadline
SRCS = minishell.c $(SRC_PATH)parsing.c $(SRC_PATH)struct_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): lib $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(CFLAGS)

lib:
	$(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJS)
	@rm -f .*.swp
	@rm -f */.*.swp
	@rm -f a.out
	$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
