/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:10:47 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 05:11:02 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "collector.h"

size_t	ft_wordlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

char	*ft_strjoinwithslash(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	char	*res;

	len1 = 0;
	while (s1[len1])
		len1++;
	res = f_malloc(len1 + ft_wordlen(s2) + 2);
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	i = -1;
	res[len1] = '/';
	while (s2[++i] && s2[i] != ' ')
		res[i + len1 + 1] = s2[i];
	res[i + len1 + 1] = 0;
	return (res);
}
