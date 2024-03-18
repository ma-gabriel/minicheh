/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 02:27:31 by geymat            #+#    #+#             */
/*   Updated: 2024/03/18 10:27:36 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	loops_minishell(t_env **env)
{
	char	*line;

	line = malloc(1);
	if (line)
		line[0] = 0;
	while (line && ft_strncmp(line, "exit", 42))
	{
		free(line);
		line = NULL;
		signal(SIGINT, &sahandler_true);
		line = get_a_new_line(*env);
		signal(SIGINT, &sahandler_fake);
		if (!line)
			return ;
		executions(line, env);
	}
	if (line)
		free(line);
}
