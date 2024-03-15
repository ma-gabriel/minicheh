/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:11:22 by geymat            #+#    #+#             */
/*   Updated: 2024/03/15 03:45:26 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

static int	check_args_exit(char *line)
{
	while (*line)
	{
		if (!ft_isdigit(*line) && *line != ' ')
		{
			write(2, "minishell: exit: numeric argument required\n", 44);
			return (1);
		}
		if (*line == ' ')
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			return (2);
		}
		line ++;
	}
	return (0);
}

int	bi_exit(char *line)
{
	char	*line_cpy;
	int	res;
	int	args_flag;

	line_cpy = line;
	while (*line == ' ')
		line++;
	line += 4;
	while (*line == ' ')
		line++;
	if (!(*line))
		return (-1);
	args_flag = check_args_exit(line);
	res = 1;
	if (args_flag == 1)
		return (the_return_value(1));
	else if (args_flag == 0)
		res = ft_atoi(line);
	ft_strlcpy(line_cpy, "exit", 5);
	return (the_return_value(res % 256));
}
