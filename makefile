# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/23 16:37:33 by tpouget           #+#    #+#              #
#    Updated: 2021/09/15 14:36:55 by bajaba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################
##	VARIABLES	##
##################

SHELL			=	zsh
NAME			=	minishell

#CC			  	=	gcc-11
CC			  	=	clang

INCLUDE_FLAGS	=	-Iinc -Ilibft
ifeq ($(shell uname -s),Darwin)
INCLUDE_FLAGS	+=	-I/opt/homebrew/Cellar/readline/8.1.2/include
endif

#Add -Werror before correction 
CFLAGS			=	${INCLUDE_FLAGS} -Wall -Wextra -g3 

#Our beloved address sanitizer
#CFLAGS			+=	-fsanitize=address
#LFLAGS			+=	-fsanitize=address

#Works with gcc version 10 and 11
#CFLAGS			+=	-fanalyzer

#Get sources from src/ directory
SRC/SOURCES		=	$(wildcard src/*.c)
#SRC/SOURCES	+=	$(wildcard src/*/*.c)
#SRC/SOURCES	=	$(shell ls src/**/*.c)

INC/HEADERS		=	$(wildcard inc/*.h)

ifeq ($(shell uname -s),Darwin)
LFLAGS			=	-L /opt/homebrew/Cellar/readline/8.1.2/lib
endif
LFLAGS			+=	-lreadline -L./libft -lft 

#Use if sources are in src/ directory
OBJ/OBJECTS		=	$(patsubst src/%.c, obj/%.o, $(SRC/SOURCES))

##############
##	RULES	##
##############

all:			$(NAME)

$(NAME):		${OBJ/OBJECTS} libft/libft.a
				@echo "Linking..."
				${CC} ${LFLAGS} ${OBJ/OBJECTS} -o $@ 

obj/%.o:		src/%.c Makefile | obj
				${CC} ${CFLAGS} -c $< -o $@

libft/libft.a:
				$(MAKE) -C libft

obj:			
				mkdir obj

clean:			
				rm -rf obj

fclean:			clean
				rm -rf $(NAME)

re:				fclean all

.PHONY:			all clean fclean re test
