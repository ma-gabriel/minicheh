NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g3
HEADER = -I inc -I libft
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
	build_in_pwd.c \
	build_in_cd.c \
	execution.c \
	kind_of_pipex/almost_libft_utils.c \
	kind_of_pipex/execve_stuff.c \
	kind_of_pipex/ft_split.c \
	kind_of_pipex/ft_strjoins.c \
	kind_of_pipex/get_next_line.c \
	kind_of_pipex/get_next_line_utils.c \
	kind_of_pipex/open_close_free.c \
	kind_of_pipex/pipex.c \
	kind_of_pipex/builts-in.c

SRCS_DIR = $(addprefix srcs/, $(SRCS))
OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(HEADER) -Llibft -lft -lreadline

$(OBJS_DIR)/%.o: srcs/%.c
	mkdir -p $(OBJS_DIR)/kind_of_pipex
	$(CC) $(FLAGS) $(HEADER) -c $< -o $@ -I./inc -I./libft

$(LIBFT):
	cd ./libft && $(MAKE) all

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
