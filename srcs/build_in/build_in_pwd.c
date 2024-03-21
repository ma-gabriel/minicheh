/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:13:29 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 03:39:21 by lcamerly         ###   ########.fr       */
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
			f_free(path);
		errno = 0;
		path = f_malloc(i);
		if (!path)
			return (NULL);
		getcwd(path, i);
		i++;
	}
	if (!errno)
		return (path);
	if (path)
		f_free(path);
	perror("pwd");
	return (NULL);
}

int	bi_pwd(char *line, t_env **env)
{
	char	*pwd_string;

	if (!redirect_before_bi(line, env))
		return (the_return_value(1));
	pwd_string = get_pwd();
	if (!pwd_string)
		return (the_return_value(1));
	printf("%s\n", pwd_string);
	f_free(pwd_string);
	the_return_value(0);
	return (0);
}
