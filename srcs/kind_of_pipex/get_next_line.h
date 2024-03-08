/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:54:04 by geymat            #+#    #+#             */
/*   Updated: 2024/02/18 18:06:29 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_endswith(char *test);
size_t	ft_endline(char *s);
char	*ft_strjoin_free_first_gnl(char *s1, char *s2, size_t lim);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*free_ret_null(void *p);

#endif
