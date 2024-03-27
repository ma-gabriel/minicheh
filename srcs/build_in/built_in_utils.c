/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:33:38 by geymat            #+#    #+#             */
/*   Updated: 2024/03/27 13:34:06 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redirect_before_bi(char *line, int fd[2])
{
	int	res;

	fd[0] = dup(0);
	if (fd[0] == -1)
		return (0);
	fd[1] = dup(1);
	if (fd[1] == -1)
	{
		close(fd[0]);
		return (0);
	}
	res = redirections(line);
	if (res == -1)
		return (0);
	return (1);
}

int	restaure_redirections_bi(int fd[2])
{
	if (dup2(fd[0], 0) == -1 || dup2(fd[1], 1) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		f_exit(3);
		return (0);
	}
	close(fd[0]);
	fd[0] = -1;
	close(fd[1]);
	fd[1] = -1;
	return (1);
}
