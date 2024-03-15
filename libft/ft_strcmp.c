/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 04:58:29 by geymat            #+#    #+#             */
/*   Updated: 2024/03/06 05:07:02 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strcmp(const char *first, const char *second)
{
	size_t	i;

	i = 0;
	if (!(first[i]))
		return (-second[i]);
	while (first[i] && i + 1 && first[i])
	{
		if (first[i] - second[i])
			return (((unsigned char) first[i]
					- (unsigned char)second[i]));
		i++;
	}
	return (((unsigned char) first[i] - (unsigned char)second[i]));
}
