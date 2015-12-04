
NAME = minishell

SRC =	minishell.c \
		builtin.c \
		builtin_env.c \
		builtin_builtin.c \
		find_bin.c \
		annex.c \
		annex2.c

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

CC = gcc

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -I./libft -o $(NAME)

$(LIBFT):
	@make -C libft/

%.o: %.c
	@$(CC) $(FLAGS) -I./libft/ -c $< -o $@

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C ./libft/ fclean
	@rm -rf $(NAME)

re: fclean all