/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   almost_libft_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 04:48:30 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 03:47:32 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "collector.h"

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

char	*ft_strdup_until_space(const char *src)
{
	size_t	i;
	char	*dest;
	size_t	len;

	i = -1;
	len = 0;
	while (src[len] && src[len] != ' ')
		len++;
	dest = (char *) f_malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (++i < len)
		dest[i] = src[i];
	dest[i] = 0;
	return (dest);
}
