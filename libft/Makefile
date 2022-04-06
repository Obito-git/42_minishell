NAME = libft.a
CC = gcc
CFLAGS = -Iincludes -Wall -Werror -Wextra -g3

#colors:
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
ENDCOLOR="\e[0m"

SRCS = $(wildcard */*.c) 
SRCS += $(wildcard */*/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): norm $(OBJS)
	@echo ${GREEN}"Objects have been created!"${ENDCOLOR}
	@echo ""
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	@echo ${YELLOW}$(NAME)" is ready for use!"${ENDCOLOR}

norm:
	@echo ${YELLOW}"Checking norminette.."${ENDCOLOR}
	@$(eval NORM_RES :=$(shell norminette | grep "Error" | head -n1))
	@if [ ! -z "$(NORM_RES)" ]; then\
		echo ${RED}"Norm KO"${ENDCOLOR};\
		echo "";\
		exit 1;\
	else\
		echo ${GREEN}"Norm OK"${ENDCOLOR};\
	fi
	@echo ""

clean:
	rm -f $(OBJS)
	rm -f .*.swp
	rm -f */.*.swp
	rm -f */*/.*.swp
	rm -f a.out
	@echo ""
	@echo ${GREEN}"Objects and trash were successfully removed"${ENDCOLOR}

fclean: clean
	rm -f $(NAME)
	@echo ""
	@echo ${YELLOW}"Project is clear!"${ENDCOLOR}

re: fclean all

.PHONY: all clean fclean re bonus

