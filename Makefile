# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geymat <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 04:17:20 by geymat            #+#    #+#              #
#    Updated: 2024/03/06 08:35:31 by geymat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = main.c \
       loop_minishell.c \
       get_new_line.c \
       replace_str.c \
       create_envp.c \
       built_in_env.c

HEADERS = minishell.h

OBJECTS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(HEADERS) $(MINIHEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -I. -I./libft

$(LIBFT):
	cd ./libft && $(MAKE) all


$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -Llibft -lft -lreadline
 
clean:
	cd ./libft && $(MAKE) fclean
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: re all clean fclean
