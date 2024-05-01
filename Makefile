NAME    = minishell
 
CC      = gcc

CFLAGS  = -Wall -Wextra -Werror -g3 

RM      = rm -f

LIBFT          = libft

FT_LIBFT        = libft/libft.a

PRINTF          = ft_printf

FT_PRINTF       = ft_printf/libftprintf.a

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c test.c free.c signals.c \
					parsing/quote.c parsing/addspaces.c parsing/syntax_error.c parsing/expand.c \
					parsing/expand_2.c parsing/parsing.c parsing/token.c \
					exec/pipex1.c exec/pipex2.c exec/builtin/export.c exec/copy_env.c exec/redir_chevron.c \
					exec/builtin/unset.c exec/builtin/export_utils.c exec/builtin/built_in.c \
					exec/builtin/echo_and_cd.c exec/builtin/built_in_utils.c exec/builtin/exit.c \

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

HEAD	=	-I.

all : ${NAME}

${NAME} : ${DIR_OBJS} ${OBJS}
		${MAKE} -C ${LIBFT}
		${MAKE} -C ${PRINTF}
		${CC} ${OBJS} ${HEAD} -o ${NAME} ${FT_LIBFT} -lreadline ${FT_PRINTF}
		@echo "\033[31;5mminishell du salaaaaaaaaam\033[0m"

${OBJS} : ${DIR_OBJS}/%.o : ${DIR_SRCS}/%.c
	${CC} ${CFLAGS} ${HEAD} -c $< -o $@

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/exec
	mkdir -p objs/parsing

leaks : all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=ignore.txt   ./minishell


clean :
	${RM} ${OBJS} 
	make clean -C libft
	make clean -C ft_printf

fclean : clean
	${RM} ${NAME} 
	make fclean -C libft
	make fclean -C ft_printf
	${RM} ${FT_LIBFT}
	${RM} ${FT_PRINTF}

re : fclean all

-include $(DEPS)

.PHONY : all clean fclean leaks re

# CDFLAGS 		= -MMD -MP
# MAKEFLAGS		=	--no-print-directory

# env: $(NAME)
# env -i ./minishell
#  
#  stop:
#  rm -rf ${NAME}
#
# .SILENT: