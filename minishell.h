/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 06:04:33 by geymat            #+#    #+#             */
/*   Updated: 2024/03/06 05:16:50 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

void	loops_minishell(t_env *envp);
char    *get_a_new_line(t_env *env);
char	*replace_env(char *str, t_env *env);

#endif
