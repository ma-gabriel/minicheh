/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:03:29 by geymat            #+#    #+#             */
/*   Updated: 2024/02/18 18:06:05 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (src[i++])
		res = i;
	i = 0;
	while (src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size)
		dst[i] = 0;
	return (res);
}

size_t	ft_endline(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n' && i < BUFFER_SIZE)
		i++;
	return (i + (s[i] == '\n'));
}

void	*free_ret_null(void *p)
{
	free(p);
	return (NULL);
}

char	*ft_strjoin_free_first_gnl(char *s1, char *s2, size_t lim)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = 0;
	if (!s2)
		return (free_ret_null(s1));
	while (s1[len1])
		len1++;
	len2 = 0;
	while (s2[len2] && len2 < lim)
		len2++;
	res = (char *) malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		return (free_ret_null(s1));
	len1 = -1;
	while (s1[++len1])
		res[len1] = s1[len1];
	len2 = -1;
	while (s2[++len2] && len2 < lim)
		res[len1 + len2] = s2[len2];
	res[len1 + len2] = 0;
	free(s1);
	return (res);
}

int	ft_endswith(char *test)
{
	size_t	i;

	i = 0;
	while (test[i])
		i++;
	if (i && test[i - 1] == '\n')
		return (1);
	return (0);
}
