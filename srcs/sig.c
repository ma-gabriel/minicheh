/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:22:27 by root              #+#    #+#             */
/*   Updated: 2024/03/18 10:23:04 by lcamerly         ###   ########.fr       */
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
	if (SIGINT == sig)
	{
		write(1, "\n", 1);
		the_return_value(130);
	}
}
