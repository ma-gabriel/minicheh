/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:58:13 by geymat            #+#    #+#             */
/*   Updated: 2024/03/19 02:00:09 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	shorten_one(char *str, size_t *i,
	int *delimiter, int value)
{
	*delimiter = value;
	ft_strcpy(str + *i, str + 1 + *i);
	(*i)--;
}

void	rm_useless_quotes(char *str)
{
	int		delimiter;
	size_t	i;

	delimiter = 0;
	i = 0;
	while (str && str[i])
	{
		if (delimiter == 1 && (str[i] == '\"'))
			shorten_one(str, &i, &delimiter, 0);
		else if ((delimiter == 2) && str[i] == '\'')
			shorten_one(str, &i, &delimiter, 0);
		else if ((str[i] == '\"') && !delimiter)
			shorten_one(str, &i, &delimiter, 1);
		else if ((str[i] == '\'') && !delimiter)
			shorten_one(str, &i, &delimiter, 2);
		i++;
	}
}

void	rm_useless_quotes_argv(char **str)
{
	while (*str)
	{
		rm_useless_quotes(*str);
		str++;
	}
}
