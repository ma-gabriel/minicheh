/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 02:27:31 by geymat            #+#    #+#             */
/*   Updated: 2024/03/13 15:47:06 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int sig;


int signal_funciton(int activation, char **line, t_env **env)
{
	static char** p1 = NULL;
	static t_env** p2 = NULL;
	
    if (activation == 1)
    {
		p1 = line;
		p2 = env;
    }
    else 
    {	
        *line = ft_strdup("");
        the_return_value(p2, 130);
    }
	return (1);
}


void sahandler(int sig)
{
    if (SIGINT == sig)
    {
        signal_funciton(0, NULL, NULL);
    }
}

void	loops_minishell(t_env **env)
{
	char	*line;

	signal_funciton(1, &line, env);
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
