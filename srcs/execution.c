/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:22:00 by geymat            #+#    #+#             */
/*   Updated: 2024/03/19 01:59:30 by geymat           ###   ########.fr       */
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
		else if ((str[i] == '\'') && !delimiter)
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
	size_t	i;

	i = 0;
	while (*(line + i) == ' ')
		i++;
	if (!ft_strncmp(line + i, "env", 3) && (line[i + 3] == ' ' || !line[i + 3]))
		return (bi_env(env) || 1);
	if (!ft_strncmp(line + i, "echo", 4)
		&& (line[i + 4] == ' ' || !line[i + 4]))
		return (bi_echo(line + i) || 1);
	if (!ft_strncmp(line + i, "pwd", 3) && (line[i + 3] == ' ' || !line[i + 3]))
		return (bi_pwd() || 1);
	if (!ft_strncmp(line + i, "cd", 2) && (line[i + 2] == ' ' || !line[i + 2]))
		return (bi_cd(line + i, env) || 1);
	if (!ft_strncmp(line + i, "unset", 5) && (line[5] == ' ' || !line[i + 5]))
		return (bi_unset(line + i, env) || 1);
	if (!ft_strncmp(line + i, "export", 6)
		&& (line[i + 6] == ' ' || !line[i + 6]))
		return (bi_export(line, env) || 1);
	if (!ft_strncmp(line, "exit", 4) && (line[4] == ' ' || !line[4]))
		return (bi_exit(line) || 1);
	return (0);
}

int	redirect_before_bi(char *line, t_env **env)
{
	int	fd[2];
	int	res;

	fd[0] = dup(0);
	if (fd[0] == -1)
		return (-1);
	fd[1] = dup(1);
	if (fd[1] == -1)
	{
		close(fd[0]);
		return (-1);
	}
	res = redirections(line);
	if (res != -1)
		res = is_a_built_in(line, env);
	if (dup2(fd[0], 0) == -1 || dup2(fd[1], 1) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-(bi_exit(line) || 1));
	}
	close(fd[0]);
	close(fd[1]);
	return (res);
}

void	executions(char *line, t_env **env)
{
	char	**envp;
	char	**argv;

	envp = create_envp(*env);
	if (!envp)
	{
		the_return_value(1);
		return ;
	}
	change_string(line, '|', -2);
	argv = ft_split(line, '|');
	if (!argv)
	{
		ft_strsfree(envp);
		the_return_value(1);
		return ;
	}
	change_split(argv, -2, '|');
	rm_useless_quotes_argv(argv);
	rm_useless_quotes(line);
	if (argv[0] && (argv[1] || !(redirect_before_bi(line, env))))
		the_return_value(almost_pipex(argv, envp, (void *) env));
	ft_strsfree(envp);
	ft_strsfree(argv);
}
