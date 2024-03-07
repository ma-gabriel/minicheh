/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 02:27:31 by geymat            #+#    #+#             */
/*   Updated: 2024/03/07 05:15:52 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	loops_minishell(t_env **env)
{
	char	*line;
	
	line = malloc(0);
	while (line)
	{
		free(line);
		line = get_a_new_line(*env);
		if (!line || !ft_strncmp(line, "exit", 8))
		{
			if (line)
				free(line);
			return ;
		}
		if (!ft_strncmp(line, "env", 3) && (line[3] == ' ' || !line[3]))
			bi_env(env);
		if (!ft_strncmp(line, "echo ", 5))
			bi_echo(line, env);
		if (!ft_strncmp(line, "pwd", 3))
			bi_pwd(env);
	}
}
