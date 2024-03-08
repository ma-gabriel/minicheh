/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts-in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:43:19 by geymat            #+#    #+#             */
/*   Updated: 2024/03/08 17:40:42 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "pipex.h"

int	is_a_built_in_pipe(char *line, void *env, int fd[3])
{
	int	temp;

	temp = -1;
	if (fd[0] == -1 || fd[1] == -1 || dup2(fd[1], 1) == -1
		|| dup2(fd[0], 0) == -1)
		return (-(close_3_free(fd[0], fd[1], -1, NULL) || 1));
	close_3_free(fd[0], fd[1], -1, NULL);
	while (*line == ' ')
		line++;
	if (!ft_strncmp(line, "env", 3) && (line[3] == ' ' || !line[3]))
		temp = bi_env((t_env **) env);
	else if (!ft_strncmp(line, "echo ", 5))
		temp = bi_echo(line,(t_env **) env);
	else if (!ft_strncmp(line, "pwd", 3) && (line[3] == ' ' || !line[3]))
		temp = bi_pwd((t_env **) env);
	else if (!ft_strncmp(line, "cd ", 3))
		temp = bi_cd(line,(t_env **) env);
	if (temp != -1)
		exit((close_3_free(fd[0], fd[1], -1, NULL) || 1) * temp);
	return (-1);
}
