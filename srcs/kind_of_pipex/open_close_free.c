/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:10:42 by geymat            #+#    #+#             */
/*   Updated: 2024/03/15 03:02:31 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file, char *name, int flags)
{
	int	fd;

	if (!flags)
		fd = open(file, O_RDONLY);
	if (flags == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (flags == 3)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		print_error(name, strerror(errno), file);
	return (fd);
}

int	close_3_free(int fd1, int fd2, int fd3, void *allocation)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	if (allocation)
	{
		f_free(allocation);
		return (-1);
	}
	return (-2);
}

void	free_the_split(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		f_free(argv[i++]);
	f_free(argv);
}
