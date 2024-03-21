/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:55:47 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 02:43:09 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sahandler_true(int sig)
{
	if (SIGINT == sig)
	{
		the_return_value(130);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sahandler_fake(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	if (sig == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
}

void	sahandler_p_heredoc(int sig)
{
	if (sig == SIGINT)
		write(2, "^C\n", 3);
}

void	sahandler_s_heredoc(int sig)
{
	if (sig == SIGINT)
		fake_exit(130);
}
