/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:54:44 by geymat            #+#    #+#             */
/*   Updated: 2024/03/24 21:31:37 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*shorten_command(char *command)
{
	size_t	i;

	i = 0;
	command = ft_strdup(command);
	if (!command)
		return (NULL);
	while (*command == ' ')
		command++;
	while (command[i] && command[i] != ' ')
		i++;
	command[i] = 0;
	replace_chars_in_str(command, -1, ' ');
	rm_useless_quotes(command);
	return (command);
}

char	*find_command(char **paths, char *command, int i)
{
	char	*path;
	size_t	len;

	command = shorten_command(command);
	if (!paths || !command)
		return (NULL);
	path = ft_strdup(command);
	if (path)
		len = ft_strlen(path);
	while (path && (ft_strchr(command, '/') > command + len || !ft_strchr
			(command, '/')) && access(path, X_OK) && paths[i])
		path = ft_strjoinwithslash(paths[i++], command);
	if (paths && path && (access(path, X_OK) || !*command))
	{
		if (ft_strchr(command, '/') > command + len || ft_strchr(command, '/'))
			print_error("minishell", strerror(errno), command);
		else
			print_error("minishell", "command not found", command);
		path = NULL;
	}
	return (path);
}

int	middle_command(char *line, char **envp, int fd[3])
{
	const char	*remember_line = line;
	char		*command;
	char		**args;

	if (ft_getenv(envp, "PATH"))
		command = find_command(ft_split(ft_getenv(envp, "PATH") + 5, ':'),
				line, 0);
	else
		command = find_command(ft_split(".", ':'), line, 0);
	if (!command)
		return (close_3_free(fd[0], fd[1], -1, (char *) remember_line));
	args = ft_split(line, ' ');
	replace_chars_in_argv(args, -1, ' ');
	rm_useless_quotes_argv(args);
	if (!args)
		return (close_3_free(fd[0], fd[1], -1, command));
	close_3_free(fd[0], fd[1], -1, (char *) remember_line);
	execve(command, args, envp);
	return (0);
}

int	the_execve_stuff(char *command, char *envp[], int fd[3], t_env **env)
{
	int		pid;
	int		res;
	char	*line;

	pid = fork();
	if (pid != 0)
		return (pid);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (fd[2] != -1)
		close(fd[2]);
	fd[2] = -1;
	if (fd[0] == -1 || fd[1] == -1 || dup2(fd[1], 1) == -1 \
			|| dup2(fd[0], 0) == -1)
		return (-(close_3_free(fd[0], fd[1], -1, NULL) || 1));
	close_3_free(fd[0], fd[1], -1, NULL);
	is_a_built_in_pipe(command, env, fd);
	res = redirections(command);
	if (res == -1 || res == -2)
		return (res);
	line = ft_strdup(command);
	middle_command(line, envp, fd);
	return (-4);
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
			f_exit(close_3_free(fd_old[0], fd_old[1], -1, NULL));
		if (!argv[i + 1])
			merge_fd(-1, init_fd[1], fd_new);
		merge_fd(fd_old[0], fd_new[1], fd_merged);
		fd_merged[2] = fd_new[0];
		pid = the_execve_stuff(argv[i], envp, fd_merged, env);
		if (pid < 0)
			ultimate_exit(fd_old, fd_new, pid);
		close_3_free(fd_old[0], fd_old[1], fd_new[1], NULL);
		fd_old[0] = fd_new[0];
	}
	return (pid + 0 * close_3_free(fd_old[0], fd_old[1], -1, NULL));
}
