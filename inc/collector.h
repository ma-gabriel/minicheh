/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:33:16 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 03:40:46 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H
# include <stdlib.h>

typedef struct s_alloc
{
	void			*alloc;
	struct s_alloc	*next;
}	t_alloc;

void	add_del_everything(void *alloc, short delete);
void	*f_malloc(size_t len);
void	f_exit(int code);
void	f_free(void *alloc);

#endif
