/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 02:14:37 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 02:15:07 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/collector.h"

void	*fake_malloc(size_t len)
{
	void	*alloc;

	alloc = malloc(len);
	add_del_everything(alloc, 0);
	return (alloc);
}

void	fake_exit(int code)
{
	add_del_everything(NULL, 1);
	exit(code);
}

void	fake_free(void *alloc)
{
	add_del_everything(alloc, 2);
}
