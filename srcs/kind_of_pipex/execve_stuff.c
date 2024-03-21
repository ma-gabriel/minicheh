/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:54:44 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 03:28:07 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command(char **paths, char *command, int i)
{
	char	*path;
	size_t	len;

	if (!paths)
		return (NULL);
	path = ft_strdup_until_space(command);
	(void) ( (size_t) path && (len = ft_strlen_p(path)));
	while (path && (ft_strchr(command, '/') > command + len || !ft_strchr
			(command, '/')) && access(path, X_OK) && paths[i])
	{
		free(path);
		path = ft_strjoinwithslash(paths[i++], command);
	}
	if (paths && path && access(path, X_OK))
	{
		if (ft_strchr(command, '/') > command + len || ft_strchr(command, '/'))
			print_error("minishell", strerror(errno), path);
		else
			print_error("minishell", "command not found", path
				+ ft_strlen_p(paths[i - 1]) + 1);
		free(path);
		path = NULL;
	}
	free_the_split(paths);
	return (path);
}

int	middle_command(char *line, char **envp, int fd[3])
{
	const char	*remember_line = line;
	char		*command;
	char		**args;

	while (*line == ' ')
		line++;
	if (ft_getenv(envp, "PATH"))
		command = find_command(ft_split(ft_getenv(envp, "PATH") + 5, ':'),
				line, 0);
	else
		command = find_command(ft_split(".", ':'), line, 0);
	if (!command)
		return (close_3_free(fd[0], fd[1], -1, (char *) remember_line));
	args = ft_split(line, ' ');
	if (!args)
		free((char *) remember_line);
	if (!args)
		return (close_3_free(fd[0], fd[1], -1, command));
	close_3_free(fd[0], fd[1], -1, (char *) remember_line);
	execve(command, args, envp);
	free_the_split(args);
	free(command);
	return (0);
}

static char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*dest;
	size_t	len;

	i = -1;
	len = 0;
	while (src[len])
		len++;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	while (++i < len)
		dest[i] = src[i];
	dest[i] = 0;
	return (dest);
}

int	the_execve_stuff(char *command, char *envp[], int fd[3], t_env **env)
{
	int		pid;
	int		res;
	char	*line;

	pid = fork();
	if (pid != 0)
		return (pid);
	if (fd[2] != -1)
		close(fd[2]);
	fd[2] = -1;
	if (fd[0] == -1 || fd[1] == -1 || dup2(fd[1], 1) == -1 \
			|| dup2(fd[0], 0) == -1)
		return (-(close_3_free(fd[0], fd[1], -1, NULL) || 1));
	close_3_free(fd[0], fd[1], -1, NULL);
	is_a_built_in_pipe(command, env, fd);
	res = redirections(command, *env);
	if (res == -1 || res == -2)
		return (res);
	line = ft_strdup(command);
	middle_command(line, envp, fd);
	return (-1);
}

int	loops_executions(char **argv, char **envp, int init_fd[2], t_env **env)
{
	size_t	i;
	int		fd_old[2];
	int		fd_new[2];
	int		fd_merged[3];
	int		pid;

	merge_fd(init_fd[0], i = -1, fd_old);
	while (argv[++i])
	{
		if (argv[i + 1] && pipe(fd_new))
			exit(close_3_free(fd_old[0], fd_old[1], -1, NULL));
		if (!argv[i + 1])
			merge_fd(-1, init_fd[1], fd_new);
		merge_fd(fd_old[0], fd_new[1], fd_merged);
		fd_merged[2] = fd_new[0];
		pid = the_execve_stuff(argv[i], envp, fd_merged, env);
		if (pid == -1 || pid == -2)
		{
			close_3_free(fd_old[0], fd_old[1], fd_new[0], NULL);
			exit(127 - 3 * pid + 0 * close(fd_new[1]));
		}
		close_3_free(fd_old[0], fd_old[1], fd_new[1], NULL);
		fd_old[0] = fd_new[0];
	}
	return (pid + 0 * close_3_free(fd_old[0], fd_old[1], -1, NULL));
}
