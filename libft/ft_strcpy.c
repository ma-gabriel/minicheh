/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:05:26 by geymat            #+#    #+#             */
/*   Updated: 2024/03/18 23:13:30 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcpy(char *string1, const char *string2)
{
	size_t	i;

	if (!string2 || !string1)
		return (NULL);
	i = 0;
	while (string2[i])
	{
		string1[i] = string2[i];
		i++;
	}
	string1[i] = 0;
	return (string1);
}
