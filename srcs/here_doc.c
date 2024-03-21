/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 04:23:47 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 05:58:01 by geymat           ###   ########.fr       */
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

static void	clean_the_mess(char *line, char *limiter)
{
	if (line)
		f_free(line);
	else
	{
		write(2, "minishell: warning: here-document delimited"
			"by end-of-file\n", 59);
	}
	f_free(limiter);
}

static void	open_heredocs(char *command, int fd, t_env *env)
{
	char	*limiter;
	char	*line;
	size_t	len;

	limiter = get_limiter(command);
	signal(SIGINT, &sahandler_s_heredoc);
	if (!limiter)
		return ;
	line = readline(">");
	if (line)
		line = replace_env(line, env);
	if (line)
		len = ft_strlen(line);
	while (line && ft_strcmp(line, limiter))
	{
		write(fd, line, len);
		write(fd, "\n", 1);
		f_free(line);
		line = readline(">");
		if (line)
			line = replace_env(line, env);
		if (line)
			len = ft_strlen(line);
	}
	clean_the_mess(line, limiter);
}

static int	the_parent(void)
{
	int	kid;
	int	fd;

	signal(SIGINT, &sahandler_p_heredoc);
	wait(&kid);
	fd = open(".here_doc", O_RDONLY);
	if (fd == -1)
		return (-1);
	if (WIFEXITED(kid) && WEXITSTATUS(kid) != 130)
		return (fd);
	close(fd);
	signal(SIGINT, &sahandler_fake);
	return (-1);
}

int	get_heredoc(char *line, t_env *env)
{
	int	pid;
	int	fd;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid)
		return (the_parent());
	fd = open(".here_doc", O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
	{
		perror("minishell's here_doc");
		return (-1);
	}
	open_heredocs(line, fd, env);
	close(fd);
	f_exit(0);
	return (0);
}
