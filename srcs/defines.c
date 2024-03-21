/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 02:14:37 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 03:39:40 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/collector.h"

void	*f_malloc(size_t len)
{
	void	*alloc;

	alloc = malloc(len);
	add_del_everything(alloc, 0);
	return (alloc);
}

void	f_exit(int code)
{
	add_del_everything(NULL, 1);
	exit(code);
}

void	f_free(void *alloc)
{
	add_del_everything(alloc, 2);
}
