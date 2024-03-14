/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 02:27:31 by geymat            #+#    #+#             */
/*   Updated: 2024/03/14 10:44:55 by lcamerly         ###   ########.fr       */
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
		line = NULL;
		signal(SIGINT, &sahandler_true);
		line = get_a_new_line(*env);
		signal(SIGINT, &sahandler_fake);
		if (!line || (!ft_strncmp(line, "exit", 4) && (line[4] == ' ' || !line[4])))
		{
			if (line)
				free(line);
			return ;
		}
		executions(line, env);
	}
}
