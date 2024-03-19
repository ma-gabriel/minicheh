/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 04:23:47 by geymat            #+#    #+#             */
/*   Updated: 2024/03/19 06:14:00 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_limiter(char *line)
{
	size_t	start;
	size_t	end;
	char	*res;

	start = 0;
	while (line[start] && line[start] == ' ')
		start++;
	end = start;
	while (line[end] && line[end] != ' ')
		end++;
	res = malloc(end - start + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, line, end - start + 1);
	return (res);
}

static int	open_heredocs(char *command, int fd, t_env *env)
{
	char	*limiter;
	char	*line;
	size_t	len;

	limiter  = get_limiter(command);
	if (!limiter)
		return (-1);
	line = readline(">");
	if (line)
		len = ft_strlen(line);
	while (line && ft_strcmp(line, limiter))
	{
		write(fd, line, len);
		write(fd, "\n", 1);
		free(line);
		line = readline(">");
		if (line)
			line = replace_env(line, env);
		if (line)
			len = ft_strlen(line);
	}
	if (line)
		free(line);
	else
	{
		write(2, "minishell: warning: here-document delimited by end-of-file (wanted `", 69);
		write(2, limiter, ft_strlen(limiter));
		write(2, "')\n", 3);
	}
	free(limiter);
	return (0);
}

int	get_heredoc(char *line, t_env *env)
{
	int	pid;
	int	fd;
	int	kid;
	
	fd = open(".here_doc", O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (fd == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd);
		return (-1);
	}
	if (pid)
	{
		wait(&kid);
		if (WIFEXITED(kid) && WEXITSTATUS(kid) != -1)
			return (fd);
		close(fd);
		return (-1);
	}
	kid = open_heredocs(line, fd, env);
	close(fd);
	exit(kid);
}
