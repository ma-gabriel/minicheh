/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:43:19 by geymat            #+#    #+#             */
/*   Updated: 2024/03/19 06:43:40 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "pipex.h"

static void	destruction(char *line, t_env **env, int fd[3], int temp)
{
	if (temp != -2)
	{
		if (temp == -1)
			temp = 0;
		free(line);
		ft_envclear(*env);
		exit((close_3_free(fd[0], fd[1], -1, NULL) || 1) * temp);
	}
}

int	is_a_built_in_pipe(char *line, t_env **env, int fd[3])
{
	int		temp;
	size_t	i;

	temp = -2;
	i = 0;
	while (*(line + i) == ' ')
		i++;
	if (!ft_strncmp(line + i, "env", 3) && (line[3 + i] == ' ' || !line[3 + i]))
		temp = bi_env(line, env);
	else if (!ft_strncmp(line + i, "echo ", 5))
		temp = bi_echo(line, env);
	else if (!ft_strncmp(line + i, "pwd", 3)
		&& (line[3 + i] == ' ' || !line[3 + i]))
		temp = bi_pwd(line, env);
	else if (!ft_strncmp(line + i, "cd", 2)
		&& (line[2 + i] == ' ' || !line[2 + i]))
		temp = bi_cd(line, env);
	else if (!ft_strncmp(line + i, "exit", 4)
		&& (line[4 + i] == ' ' || !line[4 + i]))
		temp = bi_exit(line, env);
	if (temp != -2)
		destruction(line, env, fd, temp);
	return (-1);
}
