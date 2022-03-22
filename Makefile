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

NAME			=	minishell

CC			  	=	gcc-11
#CC			  	=	clang

INCLUDE_FLAGS	=	-Iinc -Ilibft
ifeq ($(shell uname -s),Darwin)
INCLUDE_FLAGS	+=	-I/opt/homebrew/Cellar/readline/8.1.2/include
endif

#Add -Werror before correction 
CFLAGS			=	${INCLUDE_FLAGS} -Wall -Wextra -g3 

#Our beloved address sanitizer
asan			=	-fsanitize=address	
#CFLAGS			+=	$(asan)	
#LDFLAGS			+=	$(asan)	

#Works with gcc version 10 and 11
#CFLAGS			+=	-fanalyzer

#Get sources from src/ directory
SRC/SOURCES		=	$(wildcard src/*.c)
#SRC/SOURCES	+=	$(wildcard src/*/*.c)
#SHELL			=	zsh
#SRC/SOURCES	=	$(shell ls src/**/*.c)

INC/HEADERS		=	$(wildcard inc/*.h)

ifeq ($(shell uname -s),Darwin)
LDFLAGS			=	-L/opt/homebrew/Cellar/readline/8.1.2/lib
endif
LDFLAGS			+=	-L./libft

LDLIBS			=	-lreadline -lft 

#Use if sources are in src/ directory
OBJ/OBJECTS		=	$(patsubst src/%.c, obj/%.o, $(SRC/SOURCES))

##############
##	RULES	##
##############

all:			$(NAME)

$(NAME):		${OBJ/OBJECTS} libft/libft.a
				@echo "Linking..."
				@# LDFLAGS (-L) always come before oject files !
				${CC} -o $@ ${LDFLAGS} ${OBJ/OBJECTS} ${LDLIBS}

obj/%.o:		src/%.c ${INC/HEADERS} Makefile | obj
				${CC} ${CFLAGS} -c $< -o $@

libft/libft.a:
				$(MAKE) -C libft

obj:			
				mkdir obj

clean:			
				$(MAKE) -C libft clean
				rm -rf obj
				$(MAKE) -C libft clean

fclean:			clean
				$(MAKE) -C libft fclean
				rm -rf $(NAME)
				rm -rf libft/libft.a

re:				fclean all

.PHONY:			all clean fclean re test
