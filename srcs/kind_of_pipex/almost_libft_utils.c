/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   almost_libft_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 04:48:30 by geymat            #+#    #+#             */
/*   Updated: 2024/02/22 17:53:11 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strcmp_nl(const char *first, const char *second)
{
	size_t	i;

	i = 0;
	if (!(first[i]))
		return (-second[i]);
	while (first[i] && i + 1 && first[i] != '\n')
	{
		if (first[i] - second[i])
			return (((unsigned char) first[i]
					- (unsigned char)second[i]));
		i++;
	}
	if (first[i] == '\n')
		return ((unsigned char) second[i]);
	return (((unsigned char) first[i] - (unsigned char)second[i]));
}

char	*ft_strchr(char *str, int c)
{
	size_t	i;

	i = -1;
	while (str[++i])
		if (str[i] == (char) c)
			return (str + i);
	if (!((char) c))
		return (str + i);
	return (0);
}

char	*ft_strdup_until_space(const char *src)
{
	size_t	i;
	char	*dest;
	size_t	len;

	i = -1;
	len = 0;
	while (src[len] && src[len] != ' ')
		len++;
	dest = (char *) malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (++i < len)
		dest[i] = src[i];
	dest[i] = 0;
	return (dest);
}
