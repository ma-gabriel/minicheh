/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:59:08 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 04:32:05 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/collector.h"
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	res = 0;
	while (s[i])
		i++;
	if (i < start)
		res = f_malloc(1);
	else if (i - start <= len)
		res = f_malloc(i - start + 1);
	else if (i - start > len)
		res = f_malloc(len + 1);
	if (!res)
		return (NULL);
	if (i < start)
	{
		*res = 0;
		return (res);
	}
	i = 0;
	while (s[i++ + start] && i - 1 < len)
		res[i - 1] = s[i + start - 1];
	res[i - 1] = 0;
	return (res);
}
