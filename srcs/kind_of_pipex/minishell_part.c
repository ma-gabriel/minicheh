/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:43:19 by geymat            #+#    #+#             */
/*   Updated: 2024/03/12 09:42:38 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "pipex.h"

/*
int	redirections(char **line, int fd[2])
{
	char *ft_substr()
}*/

int	is_a_built_in_pipe(char *line, void *env, int fd[3])
{
	int	temp;
	size_t	i;

	temp = -1;
	if (fd[0] == -1 || fd[1] == -1 || dup2(fd[1], 1) == -1
		|| dup2(fd[0], 0) == -1)
		return (-(close_3_free(fd[0], fd[1], -1, NULL) || 1));
	close_3_free(fd[0], fd[1], -1, NULL);
	i = 0;
	while (*(line + i) == ' ')
		i++;
	if (!ft_strncmp(line + i, "env", 3) && (line[3 + i] == ' ' || !line[3 + i]))
		temp = bi_env((t_env **) env);
	else if (!ft_strncmp(line + i, "echo ", 5))
		temp = bi_echo(line,(t_env **) env);
	else if (!ft_strncmp(line + i, "pwd", 3) && (line[3 + i] == ' ' || !line[3 + i]))
		temp = bi_pwd((t_env **) env);
	else if (!ft_strncmp(line + i, "cd ", 3))
		temp = bi_cd(line,(t_env **) env);
	if (temp != -1)
	{
		free(line);
		ft_envclear(*((t_env **)env));
		exit((close_3_free(fd[0], fd[1], -1, NULL) || 1) * temp);
	}
	return (-1);
}
