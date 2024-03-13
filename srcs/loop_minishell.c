/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 02:27:31 by geymat            #+#    #+#             */
/*   Updated: 2024/03/13 12:44:04 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int sig;

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
		executions(line, env);
	}
}
