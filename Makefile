.DEFAULT_GOAL : $(NAME)

NAME = 

CC = cc

CFLAGS = -Werror -Wall -Wextra -g3

RM = rm -rf

SRCS =  srcs/main.c \
	srcs/dinner_loop.c \
	srcs/monitor_dinner.c \
	srcs/utils/error_utils.c \
	srcs/utils/mutex_safe.c \
	srcs/utils/print_msg_mutex.c \
	srcs/utils/thread_safe.c \
	srcs/utils/time_utils.c \
	srcs/libft_ext/atoi_perr.c \
	srcs/libft_ext/calloc_safe.c \


OBJS = ${SRCS:.c=.o}

_CLEAR	= \033[0K\r\c
_OK	= [\033[32mOK\033[0m]

all : force $(NAME)

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} -g3 -I include -I libft/ -o $@ $^ -Llibft -lft -lreadline
	@echo "$(_OK) $(NAME) compiled"

${NAME_BONUS}: ${OBJS}
	@${CC} ${CFLAGS} -g3 -I include -I libft/ -o $@ $^ -Llibft -lft -lreadline
	@echo "$(_OK) $(NAME_BONUS) compiled"

%.o: %.c  include/minishell.h libft/libft.h
	@echo "[..] $(NAME_SHORT)... compiling $*.c\r\c"
	@${CC} ${CFLAGS} -g3 -Iinclude -Ilibft/ -c $< -o $@
	@echo "$(_CLEAR)"

force :
	make -C libft

clean :
	@$(MAKE) -C $(LIBFT_DIR) clean -s
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_BONUS)

fclean : clean
	@$(MAKE) -C $(LIBFT_DIR) fclean -s
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)

re : fclean all

.PHONY: all clean fclean re force bonus

