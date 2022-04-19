# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/23 16:37:33 by tpouget           #+#    #+#              #
#    Updated: 2022/04/14 18:44:21 by tpouget          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################
##	VARIABLES	##
##################

NAME			=	minishell

CC				=	clang
#CC			  	=	gcc-11

INCLUDE_FLAGS	=	-Iinc -I libft/includes
ifeq ($(shell uname -s),Darwin)
INCLUDE_FLAGS	+=	-I/opt/homebrew/Cellar/readline/8.1.2/include
endif

#Add -Werror before correction 
CFLAGS			=	${INCLUDE_FLAGS} -Wall -Wextra -g3 -Werror

#Our beloved address sanitizer
#ASAN			=	-fsanitize=address	
CFLAGS			+=	$(GCC_ANALYZER)	
CFLAGS			+=	$(ASAN)	
LDFLAGS			+=	$(ASAN)	

#Works with gcc version 10 and 11
#CFLAGS			+=	-fanalyzer

#Get sources from src/ directory
#SRC/SOURCES		=	$(wildcard src/*.c)
#SRC/SOURCES	+=	$(wildcard src/*/*.c)
SHELL			=	zsh
SRC/SOURCES		=	$(shell ls src/**/*.c)

INC/HEADERS		=	$(wildcard inc/*.h)

ifeq ($(shell uname -s),Darwin)
LDFLAGS			=	-L/opt/homebrew/Cellar/readline/8.1.2/lib
endif
LDFLAGS			+=	-L./libft

LDLIBS			=	-lreadline -lft 

#Use if sources are in src/ directory
#OBJ/OBJECTS		=	$(addprefix obj/, $(notdir $(patsubst src/%.c, obj/%.o, $(SRC/SOURCES))))
OBJ/OBJECTS		=	$(patsubst src/%.c, obj/%.o, $(SRC/SOURCES))

##############
##	RULES	##
##############

all:			$(NAME)

$(NAME):		${OBJ/OBJECTS}
				$(MAKE) -C libft
				@echo "Linking..."
				@# LDFLAGS (-L) always come before oject files !
				${CC} -o $@ ${LDFLAGS} $^ ${LDLIBS}

obj/%.o:		src/%.c ${INC/HEADERS} Makefile | obj
				${CC} ${CFLAGS} -c $< -o $@

obj:			
				mkdir obj
				mkdir obj/expansion_handling

clean:			
				$(MAKE) -C libft clean
				rm -rf obj

fclean:			clean
				$(MAKE) -C libft fclean
				rm -rf $(NAME)
				rm -rf libft/libft.a

re:				fclean all

.PHONY:			all clean fclean re test
