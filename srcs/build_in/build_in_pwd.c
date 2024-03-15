/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:13:29 by geymat            #+#    #+#             */
/*   Updated: 2024/03/14 01:14:00 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_pwd(void)
{
	char	*path;
	size_t	i;

	i = 1;
	path = NULL;
	errno = 34;
	while (errno == 34)
	{
		if (path)
			free(path);
		errno = 0;
		path = malloc(i);
		if (!path)
			return (NULL);
		getcwd(path, i);
		i++;
	}
	if (!errno)
		return (path);
	if (path)
		free(path);
	perror("pwd");
	return (NULL);
}

int	bi_pwd(void)
{
	char	*pwd_string;

	pwd_string = get_pwd();
	if (!pwd_string)
		return (the_return_value(1));
	printf("%s\n", pwd_string);
	free(pwd_string);
	the_return_value(0);
	return (0);
}
