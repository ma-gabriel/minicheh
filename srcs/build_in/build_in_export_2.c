/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:43:06 by lcamerly          #+#    #+#             */
/*   Updated: 2024/03/20 21:43:10 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_export(char *temp, t_env **env)
{
	char	**key_value;
	t_env	*new_lst;

	key_value = sep_in_two(temp);
	if (!key_value)
		return (free_ret_1(temp));
	rm_useless_quotes(key_value[1]);
	new_lst = ft_envlstnew_frees(key_value);
	if (!new_lst)
		return (free_ret_1(temp));
	ft_envlstadd_until_sorted(env, new_lst);
	return (0);
}
