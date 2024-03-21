/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_first.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 05:09:51 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 04:32:12 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "../inc/collector.h"

char	*ft_strjoin_free_first(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!s1)
		return (NULL);
	j = ft_strlen(s1);
	i = ft_strlen(s2);
	res = f_malloc((i + j + 1) * sizeof(char));
	if (!res)
	{
		f_free(s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	i = -1;
	while (s2[++i])
		res[i + j] = s2[i];
	res[i + j] = '\0';
	f_free(s1);
	return (res);
}
