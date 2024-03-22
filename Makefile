.DEFAULT_GOAL : $(NAME)

NAME = philosophers

NAME_SHORT = philo

CC = clang

CFLAGS = -pthread -fsanitize=thread
# -Werror -Wall -Wextra
RM = rm -rf

SRCS =  srcs/main.c \
	srcs/init.c \
	srcs/dinner_loop.c \
	srcs/monitor_dinner.c \
	srcs/utils/mutex_safe.c \
	srcs/utils/getters.c \
	srcs/utils/setters.c \
	srcs/utils/misc.c \
	srcs/utils/threads_safe.c \
	srcs/utils/time_utils.c \
	srcs/utils/init_utils.c \
	srcs/libft_ext/atoi_perr.c \
	srcs/libft_ext/calloc_safe.c \


OBJS = ${SRCS:.c=.o}

_CLEAR	= \033[0K\r\c
_OK	= [\033[32mOK\033[0m]

all : $(NAME)

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} -Iincludes ${OBJS} -o ${NAME}
	@echo "$(_OK) $(NAME) compiled"


%.o: %.c  includes/philosophers.h
	@echo "[..] $(NAME_SHORT)... compiling $*.c\r\c"
	@${CC} ${CFLAGS} -Iincludes -c $< -o $@
	@echo "$(_CLEAR)"

clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re force bonus

