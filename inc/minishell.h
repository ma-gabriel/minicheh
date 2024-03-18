/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 06:04:33 by geymat            #+#    #+#             */
/*   Updated: 2024/03/18 21:25:15 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

void	loops_minishell(t_env **envp);
char	*get_a_new_line(t_env *env);
char	*replace_env(char *str, t_env *env);
int	ft_strsfree(char **strs);
char	**create_envp(t_env *env);
void	ft_envlstadd_until_sorted(t_env **lst, t_env *new_lst);
t_env	*ft_envlstnew(char *key, char *value);
int	the_return_value(size_t value);
int	replace_inside(char **p_s, size_t start, size_t end, char *s2);
void	get_sig(int signal);
void	ft_envlstadd_until_sorted(t_env **lst, t_env *new_lst);
void	ft_envclear(t_env *env);
t_env	*ft_envlstnew(char *key, char *value);
t_env	*ft_envlstnew_frees(char **key_value);
int		bi_env(t_env **env);
int		bi_echo(char *line);
int		bi_pwd(void);
int		bi_cd(char *line, t_env **env);
int		bi_exit(char *line);
int     cd(char *path);
int	almost_pipex(char **argv, char **envp, void *env);
void	executions(char *line, t_env **env);
char	*get_pwd(void);
int	is_a_built_in(char *line, t_env **env);
int	bi_unset(char *line, t_env **env);
int	ft_envlst_remove_if(t_env **start, char *line);
int	bi_export(char *line, t_env **env);
char	**sep_in_two(char *str);
size_t	word_len_until_equal(char *str);
char *ft_space_strtok(char *str);
void sahandler_fake(int sig);
void sahandler_true(int sig);
t_env *hardcode_env();
char	*get_value(char *str, t_env *env);
int	redirections(char *line);

#endif 
