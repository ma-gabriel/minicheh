/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 06:04:33 by geymat            #+#    #+#             */
/*   Updated: 2024/03/08 15:55:57 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	loops_minishell(t_env **envp);
char	*get_a_new_line(t_env *env);
char	*replace_env(char *str, t_env *env);
int	ft_strsfree(char **strs);
char	**create_envp(t_env *env);
void	ft_envlstadd_until_sorted(t_env **lst, t_env *new_lst);
t_env	*ft_envlstnew(char *key, char *value);
void	the_return_value(t_env **env, int value);
int	replace_inside(char **p_s, size_t start, size_t end, char *s2);
void get_sig(int signal);
void	ft_envlstadd_until_sorted(t_env **lst, t_env *new_lst);
void	ft_envclear(t_env *env);
t_env	*ft_envlstnew(char *key, char *value);
t_env	*ft_envlstnew_frees(char **key_value);
int		bi_env(t_env **env);
int		bi_echo(char *line, t_env **env);
int		bi_pwd(t_env **env);
int		bi_cd(char *line, t_env **env);
int     cd(char *path);
int	almost_pipex(char **argv, char **envp, void *env);
void	executions(char *line, t_env **env);
char	*get_pwd(void);
int	is_a_built_in(char *line, t_env **env);












#endif
