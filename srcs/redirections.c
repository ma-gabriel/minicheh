/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:58:32 by geymat            #+#    #+#             */
/*   Updated: 2024/03/18 21:22:40 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	path_len(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && \
			str[i] != '/' && str[i] != '-' && str[i] != '.')
			return (i);
		++i;
	}
	return (i);
}

int	redirect(char *line, size_t len, int flag)
{
	char	*file;
	int		fd_temp;
	int		res;

	fd_temp = -1;
	file = ft_substr(line, 0, len);
	if (!file)
		return (-1);
	if (flag == 0)
		fd_temp = open(file, O_RDONLY);
	//else if (flag == 1)
	//	fd = get_heredoc()
	else if (flag == 2)
		fd_temp = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (flag == 3)
		fd_temp = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_temp == -1)
		perror(file);
	free(file);
	if (fd_temp == -1)
		return (-1);
	res = dup2(fd_temp, flag / 2);
	close(fd_temp);
	return (res);
}

int	line_shortener(char *line, int flag)
{
	int		spaces;
	size_t	len;
	int		returned;

	returned = -1;
	spaces = 0;
	if (line[1] == '>' && flag == 0)
		write(2, "we can't handle that redirection\n", 35);
	while (*(line + (flag == 1 || flag == 3) + spaces + 1) == ' ')
		spaces++;
	len = path_len(line + (flag == 1 || flag == 3) + spaces + 1);
	if (len != 0)
		returned = redirect(line + (flag == 1 || flag == 3) \
			+ spaces + 1, len, flag);
	else
		write(2, "minishell: syntax error near unexpected token\n", 47);
	strcpy(line, line + (flag == 1 || flag == 3) + spaces + 1 + len);
	return (-(returned == -1));
}

int	redirections(char *line)
{
	char	*temp;

	while (ft_strchr(line, '>') || ft_strchr(line, '<'))
	{
		temp = ft_strchr(line, '<');
		if (temp)
			if (line_shortener(temp, 0 + (temp[1] == '<')))
				return (-1);
		temp = strchr(line, '>');
		if (temp)
			if (line_shortener(temp, 2 + (temp[1] == '>')))
				return (-1);
	}
	return (0);
}
