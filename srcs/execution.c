/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:22:00 by geymat            #+#    #+#             */
/*   Updated: 2024/03/12 11:53:31 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	change_string(char *str, char c1, char c2)
{
	size_t	i;
	int		delimiter;

        i = 0;
        delimiter = 0;
        while (str[i])
        {
                if (delimiter == 1 && (str[i] == '\"'))
                        delimiter = 0;
                else if ((delimiter == 2) && str[i] == '\'')
                        delimiter = 0;
                else if ((str[i] == '\"') && !delimiter)
                        delimiter = 1;
                else if ((str[i] == '\'')  && !delimiter)
                        delimiter = 2;
		else if (delimiter && str[i] == c1)
			str[i] = c2;
                i++;
        }
}

static void	change_split(char **env, char c1, char c2)
{
	if (!env)
		return ;
	while (*env)
	{
		change_string(*env, c1, c2);
		env++;
	}
}

int	is_a_built_in(char *line, t_env **env)
{
	while (*line == ' ')
		line++;
	if (!ft_strncmp(line, "env", 3) && (line[3] == ' ' || !line[3]))
		return (bi_env(env) || 1);
	if (!ft_strncmp(line, "echo", 4) && (line[4] == ' ' || !line[4]))
		return (bi_echo(line, env) || 1);
	if (!ft_strncmp(line, "pwd", 3) && (line[3] == ' ' || !line[3]))
		return (bi_pwd(env) || 1);
	if (!ft_strncmp(line, "cd", 2) && (line[2] == ' ' || !line[2]))
		return (bi_cd(line, env) || 1);
	if (!ft_strncmp(line, "unset", 5) && (line[5] == ' ' || !line[5]))
		return (bi_unset(line, env) || 1);
	if (!ft_strncmp(line, "export ", 6) && (line[6] == ' ' || !line[6]))
		return (bi_export(line, env) || 1);
	return (0);
}

void executions(char *line, t_env **env)
{
	char	**envp;
	char	**argv;

	envp = create_envp(*env);
	if (!envp)
	{
		the_return_value(env, 1);
		return ;
	}
	change_string(line, '|', -2);
	argv = ft_split(line, '|');
	if (!argv)
	{
		ft_strsfree(envp);
		the_return_value(env, 1);
		return ;
	}
	change_split(argv, -2, '|');
	if (argv[0] && (argv[1] || !(is_a_built_in(argv[0], env))))
		the_return_value(env, almost_pipex(argv, envp, (void *) env));
	ft_strsfree(envp);
	ft_strsfree(argv);
}
