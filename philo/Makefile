.DEFAULT_GOAL : $(NAME)

NAME = philo

NAME_SHORT = philo

CC = clang

CFLAGS_SAN = -g3 -pthread -fsanitize=thread
CFLAGS = -Werror -Wall -Wextra -pthread -g3 

RM = rm -rf

SRCS =  srcs/main.c \
	srcs/init.c \
	srcs/dinner_loop.c \
	srcs/lone_philo.c \
	srcs/dinner_end.c \
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
	@$(RM) $(NAME) philo_val philo_san

re : fclean all

sanitize : re
	@${CC} ${CFLAGS_SAN} -Iincludes ${OBJS} -o philo_san
	@echo "$(_OK) philo_san compiled"
	./philo_san 1 410 200 200 0

val : re
	@${CC} ${CFLAGS} -Iincludes ${OBJS} -o philo_val
	@echo "$(_OK) philo_val compiled"
	valgrind ./philo_val 3 405 200 200 3

test1 : re
	./$(NAME) 3 610 200 200 3
test2 : re
	./$(NAME) 4 410 200 200
test3 : re
	./$(NAME) 4 410 200 200 1
test4 : re
	./$(NAME) 200 420 200 200 10
test5 : re
	./$(NAME) 15 630 200 200 3
test6 : re
	./$(NAME) 1 630 200 200 3
test7 : re
	./$(NAME) 4 380 200 200 
test8 : re
	./$(NAME) 0 380 200 200
test9 : re
	./$(NAME) 4 380 200 200 1

.PHONY: all clean fclean re force bonus sanitize val test1 test2 test3 test4 test5 test6 test7 test8 test9
