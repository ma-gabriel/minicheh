/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:58:32 by geymat            #+#    #+#             */
/*   Updated: 2024/03/20 21:52:01 by lcamerly         ###   ########.fr       */
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

static int	open_dup2(char *line, size_t len, int flag, t_env *env)
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
	else if (flag == 1)
		fd_temp = get_heredoc(line, env);
	else if (flag == 2)
		fd_temp = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (flag == 3)
		fd_temp = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_temp == -1 && flag != 1)
		perror(file);
	free(file);
	if (fd_temp == -1)
		return (-1);
	res = dup2(fd_temp, flag / 2);
	close(fd_temp);
	return (res);
}

static int	line_shortener(char *line, int flag, t_env *env)
{
	int		spaces;
	size_t	len;
	int		returned;

	returned = -1;
	spaces = 0;
	if (line[1] == '>' && flag == 0)
		write(2, "we can't handle that redirection\n", 34);
	while (*(line + (flag == 1 || flag == 3) + spaces + 1) == ' ')
		spaces++;
	len = path_len(line + (flag == 1 || flag == 3) + spaces + 1);
	if (len != 0)
		returned = open_dup2(line + (flag == 1 || flag == 3) \
				+ spaces + 1, len, flag, env);
	else
		write(2, "minishell: syntax error near unexpected token\n", 47);
	ft_strcpy(line, line + (flag == 1 || flag == 3) + spaces + 1 + len);
	return (-(returned == -1));
}

static int	directions_hub(char *line, size_t *i, int delimiter, t_env *env)
{
	if (line[*i] == '<' && !delimiter)
	{
		if (line_shortener(line + *i, 0 + (line[*i + 1] == '<'), env))
			return (-1);
		(*i)--;
	}
	if (line[*i] == '>' && !delimiter)
	{
		if (line_shortener(line + *i, 2 + (line[*i + 1] == '>'), env))
			return (-1);
		(*i)--;
	}
	return (0);
}

int	redirections(char *line, t_env *env)
{
	size_t	i;
	int		delimiter;

	i = 0;
	delimiter = 0;
	while (line[i])
	{
		if (delimiter == 1 && line[i] == '\"')
			delimiter = 0;
		else if (delimiter == 2 && line[i] == '\'')
			delimiter = 0;
		else if (line[i] == '\"' && !delimiter)
			delimiter = 1;
		else if (line[i] == '\'' && !delimiter)
			delimiter = 2;
		if (directions_hub(line, &i, delimiter, env) == -1)
			return (-1);
		i++;
	}
	return (0);
}
