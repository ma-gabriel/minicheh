/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:10:42 by geymat            #+#    #+#             */
/*   Updated: 2024/03/22 11:45:34 by lcamerly         ###   ########.fr       */
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

void	ultimate_exit(int fd_old[2], int fd_new[2], int pid)
{
	close_3_free(fd_old[0], fd_old[1], fd_new[0], NULL);
	if (pid == -2)
		f_exit(close(fd_new[1]) || 1);
	f_exit(131 + pid + 0 * close(fd_new[1]));
}
