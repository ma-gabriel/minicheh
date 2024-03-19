/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:13:48 by geymat            #+#    #+#             */
/*   Updated: 2024/03/19 02:14:29 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	word_len_until_equal(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static void	*free_key_value(char *key, char *value)
{
	free(key);
	free(value);
	return (NULL);
}

char	**sep_in_two(char *str)
{
	char	*key;
	char	*value;
	char	**res;

	value = NULL;
	key = malloc(word_len_until_equal(str) + 1);
	if (!key)
		return (NULL);
	if (ft_strchr(str, '='))
	{
		value = ft_strdup(str + word_len_until_equal(str) + 1);
		if (!value)
		{
			free(key);
			return (NULL);
		}
	}
	res = malloc(16);
	if (!res)
		return (free_key_value(key, value));
	ft_strlcpy(key, str, word_len_until_equal(str) + 1);
	res[0] = key;
	res[1] = value;
	return (res);
}
