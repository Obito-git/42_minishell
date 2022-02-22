SHELL	=/bin/sh
cr		="\e[1;31m   - \e[0;31m"
cg		="\e[1;32m   + \e[0;32m"
cm		="\e[1;35m   > \e[0;35m"
r		="\e[0m"
n		=$(NAME)"   "
e_gcc	=$(cg)$(n)"(@) "$@" (<) "$<$(r)
size	=$(cr)$(n)$(shell du -bh $(NAME) 2>/dev/null | tr -d '$(NAME) \t')$(r)
sls		=$(shell ls $(SRC_DIR)/*/*.c 2>/dev/null | tr ' ' '\n')
q_src	=$(shell ls $(SRC_DIR)/*/*.c 2>/dev/null | wc -l | tr -d '\n')
q_obj	=$(shell ls $(OBJ_DIR)/*/*.o 2>/dev/null | wc -l | tr -d '\n')
e_src	=$(cm)$(n)$(q_src)" sources"$(r)
e_obj	=$(n)$(q_obj)" objects"
grepr	=$(shell grep -nH --color printf $(SRC_DIR)/*/*.c | grep -v "ft_printf")
grepgc	=$(shell grep -nH --color getchar $(SRC_DIR)/*/*.c)

#########################################
SRC		=	$(addsuffix .c,				\
			$(addprefix char/,			\
			ft_isalnum					\
	  		ft_isalpha					\
	  		ft_isascii					\
	  		ft_isdigit					\
	  		ft_islower					\
	  		ft_isprint					\
	  		ft_issign					\
	  		ft_isupper					\
	  		ft_tolower					\
	  		ft_toupper					\
			)							\
			$(addprefix conv/,			\
			ft_atoi_base				\
			ft_atoi						\
			ft_atol_severe				\
			ft_convert_base				\
			ft_itoabtw					\
			ft_itoa						\
			ft_nbrlen					\
			)							\
			$(addprefix debug/,			\
			debug_aux					\
			debug_coffee				\
			debug_int					\
			dbg_ar						\
			)							\
			$(addprefix file/,			\
			ft_filename					\
			ft_is_extension				\
			)							\
			$(addprefix lst/,			\
			ft_lstadd_back				\
			ft_lstadd_front				\
			ft_lstclear					\
			ft_lstdelone				\
			ft_lstiter					\
			ft_lstlast					\
			ft_lstmap					\
			ft_lstnew					\
			ft_lstsize					\
			)							\
			$(addprefix maths/,			\
			ft_abs						\
			ft_factorial				\
			ft_fibonacci				\
			ft_isprime					\
			ft_median					\
			ft_minmax					\
			ft_nextprime				\
			ft_power					\
			ft_sqrt						\
			)							\
			$(addprefix mem/,			\
			ft_bzero					\
	  		ft_calloc					\
			ft_memchr					\
	  		ft_memcmp					\
	  		ft_memcpy					\
	  		ft_memmove					\
	  		ft_memset					\
			)							\
			$(addprefix sort/,			\
			ft_insort					\
			ft_intswap					\
			ft_qsort					\
			ft_rev_int_tab				\
			ft_sort_int_tab				\
			)							\
			$(addprefix stack/,			\
			ft_stack_add_bottom			\
			ft_stack_del				\
			ft_stack_isempty			\
			ft_stack_isfull				\
			ft_stack_issort				\
			ft_stack_len				\
			ft_stack_median				\
			ft_stack_minmax				\
			ft_stack_new				\
			ft_stack_peek				\
			ft_stack_pop				\
			ft_stack_push				\
			ft_stack_rev				\
			ft_stack_show				\
			ft_stack_stats				\
			ft_stack_swap_top			\
			)							\
			$(addprefix str/,			\
			ft_arfree					\
			ft_split					\
			ft_strchr					\
			ft_strcmp					\
			ft_strcpy					\
	  		ft_strdup					\
	  		ft_striteri					\
	  		ft_strjoin					\
	  		ft_strlcat					\
	  		ft_strlcpy					\
	  		ft_strlen					\
	  		ft_strmapi					\
	  		ft_strncmp					\
	  		ft_strnstr					\
	  		ft_strrchr					\
			ft_strtolower				\
			ft_strtoupper				\
	  		ft_strtrim					\
	  		ft_substr					\
			get_next_line				\
			)							\
			$(addprefix tab/,			\
			ft_newtab					\
			ft_tab_are_distinct			\
			ft_tabdup					\
			ft_tab_issort				\
			ft_tab_median				\
			ft_tab_firstquart			\
			ft_tab_minmax				\
			ft_tabshow					\
			)							\
			$(addprefix test/,			\
			ft_test						\
			)							\
			$(addprefix write/,			\
	  		ft_printf					\
	  		ft_putarray					\
	  		ft_putchar					\
			ft_putnbase					\
			ft_putnbr					\
	  		ft_putnl					\
			ft_putptr					\
	  		ft_putstr					\
			ft_putx						\
			)							\
			)
#########################################

SRC_DIR	=	src
OBJ_DIR	=	obj
OBJ		=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

NAME	=	libft.a

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

AR		=	ar -rc

RANLIB	=	ranlib

RM		=	rm -rf

#########################################

.PHONY:	all
all:	$(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@
#\
		@echo $(e_gcc)

$(NAME):$(OBJ)
		@ar rc $(NAME) $(OBJ)
		@ranlib $(NAME)
		@echo $(cg)$(e_obj)$(r)
		@echo -n $(cg)$(n) && du -bh $(NAME) | tr -d '$(NAME)' && echo -n $(r)

.PHONY:	clean
clean:
		@$(RM) $(OBJ_DIR)
		@echo $(cr)$(e_obj)$(r)

.PHONY:	fclean
fclean:	clean
		@$(RM) $(NAME)
		@echo $(size)

.PHONY:	re
re:		fclean all

#########################################

.PHONY: a dream come true m
a:
		@echo $(e_src)"\n"$(cm)$(n)"diff check *"$(r)
		@echo $(sls) | tr ' ' '\n' | sort > o_sls.out
		@echo $(addprefix $(SRC_DIR)/, $(SRC)) | tr ' ' '\n' | sort > o_src.out
		@-diff -y --color --suppress-common-lines o_sls.out o_src.out
		@rm *.out
		@echo -n $(cm)$(n)"printf check *\n$(grepr)"$(r)
		@echo -n $(cm)$(n)"getchar check *\n$(grepgc)"$(r)

dream:	fclean
#\
		@./autoh $(shell ls $(SRC_DIR))

come:	all

true:
		@echo -n $(cm)$(n)"$(shell ar -tv $(NAME) | wc -l) scan ar objects\n"

m:		a dream come true

# # # #
# SUBDIRS = foo bar baz
#
# subdirs:
#		for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done
#
# # # #
#
# SUBDIRS = foo bar baz
#
# .PHONY: subdirs $(SUBDIRS)
#
# subdirs: $(SUBDIRS)
#
# $(SUBDIRS):
#        $(MAKE) -C $@
#
# foo: baz
