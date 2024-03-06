/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 02:27:31 by geymat            #+#    #+#             */
/*   Updated: 2024/03/06 05:19:17 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void	loops_minishell(t_env *env)
{
	char	*line;
	
	line = malloc(0);
	while (line)
	{
		free(line);
		line = get_a_new_line(env);
		if (!line || !ft_strncmp(line, "exit", 8))
		{
			if (line)
				free(line);
			return ;
		}
		//if (!ft_strncmp(line, "export ", 7))
		//	bi_export(line, &envp);
		//if (!ft_strncmp(line, "env", 3) && (line[3] == ' ' || !line[3]))
		//	bi_env(envp);
	}
}
