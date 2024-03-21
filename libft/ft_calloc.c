/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 07:35:47 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 04:32:18 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/collector.h"
void	*ft_calloc(size_t num, size_t size)
{
	char	*res;
	size_t	i;

	i = 0;
	if (num && size && ((num * size) / num != size))
		return (NULL);
	res = (char *) f_malloc(num * size);
	if (!res)
		return (NULL);
	while (i < num * size)
	{
		res[i] = 0;
		i++;
	}
	return ((void *) res);
}
