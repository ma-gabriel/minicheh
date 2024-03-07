NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
HEADER = -I inc -I libft/libft.h
LIBFT = libft/libft.a
SRCS =	built_in_echo.c \
		built_in_env.c \
		create_envp.c \
		get_new_line.c \
		loop_minishell.c \
		main.c \
		replace_str.c \
		sig.c \
		env_utils.c \

SRCS_DIR = $(addprefix srcs/, $(SRCS))
OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(HEADER) -Llibft -lft -lreadline

$(OBJS_DIR)/%.o: srcs/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(HEADER) -c $< -o $@ -I./inc -I./libft

$(LIBFT):
	cd ./libft && $(MAKE) all

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re