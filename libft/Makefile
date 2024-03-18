# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geymat <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 04:17:20 by geymat            #+#    #+#              #
#    Updated: 2024/03/18 23:35:06 by geymat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c \
       ft_isalpha.c \
       ft_memchr.c  \
       ft_memset.c \
       ft_strlcat.c \
       ft_strrchr.c \
       ft_toupper.c \
       ft_bzero.c \
       ft_isascii.c \
       ft_memcmp.c \
       ft_strchr.c \
       ft_strstr.c \
       ft_calloc.c \
       ft_isdigit.c \
       ft_memcpy.c \
       ft_strdup.c \
       ft_strlen.c \
       ft_substr.c \
       ft_isalnum.c \
       ft_isprint.c \
       ft_memmove.c \
       ft_strjoin.c \
       ft_strjoin_free_first.c \
       ft_strncmp.c \
       ft_strcmp.c \
       ft_tolower.c \
       ft_strtrim.c \
       ft_split.c \
       ft_strlcpy.c \
       ft_itoa.c \
       ft_strmapi.c \
       ft_striteri.c \
       ft_strnstr.c \
       ft_strcpy.c \
       ft_putchar_fd.c \
       ft_putstr_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c

HEADERS = libft.h

OBJECTS = $(SRCS:.c=.o)

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -I.

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

clean:
	$(RM) $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: re all clean fclean
