MAKEFLAGS        = --no-print-directory

NAME             = pipex
NAME_BONUS       = pipex_bonus

SRCS             = srcs/pipex.c srcs/pipex_utils.c
OBJS             = ${SRCS:.c=.o}

SRCS_BONUS       = srcs/pipex_bonus.c
OBJS_BONUS       = ${SRCS_BONUS:.c=.o}

CC               = cc
CFLAGS           = -Wall -Wextra -Werror -Iincludes

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: ${NAME}

bonus: ${NAME_BONUS}

${NAME}: ${OBJS}
	@make re -C ./libft
	@$(CC) ${OBJS} -Llibft -lft -o ${NAME}
	@echo "Pipex compiled."

${NAME_BONUS}: ${OBJS_BONUS}
	@make re -C ./libft
	@$(CC) ${OBJS_BONUS} -Llibft -lft -o ${NAME_BONUS}
	@echo "Pipex bonus compiled."

clean:
	@make clean -C ./libft
	@rm -f ${OBJS} ${OBJS_BONUS}
	@echo "Cleaned all object files."

fclean: clean
	@make fclean -C ./libft
	@rm -f ${NAME} ${NAME_BONUS}
	@echo "Cleaned all files."

re: fclean all

.PHONY: all clean fclean re bonus
