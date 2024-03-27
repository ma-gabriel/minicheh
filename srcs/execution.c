/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:22:00 by geymat            #+#    #+#             */
/*   Updated: 2024/03/27 13:06:37 by geymat           ###   ########.fr       */
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

int	is_a_built_in(char *line, t_env **env)
{
	size_t	i;

	i = 0;
	while (*(line + i) == ' ')
		i++;
	if (!ft_strncmp(line + i, "env", 3) && (line[i + 3] == ' ' || !line[i + 3]))
		return (bi_env(line, env) || 1);
	if (!ft_strncmp(line + i, "echo", 4)
		&& (line[i + 4] == ' ' || !line[i + 4]))
		return (bi_echo(line) || 1);
	if (!ft_strncmp(line + i, "pwd", 3) && (line[i + 3] == ' ' || !line[i + 3]))
		return (bi_pwd(line) || 1);
	if (!ft_strncmp(line + i, "cd", 2) && (line[i + 2] == ' ' || !line[i + 2]))
		return (bi_cd(line, env) || 1);
	if (!ft_strncmp(line + i, "unset", 5) && (line[5] == ' ' || !line[i + 5]))
		return (bi_unset(line, env) || 1);
	if (!ft_strncmp(line + i, "export", 6)
		&& (line[i + 6] == ' ' || !line[i + 6]))
		return (bi_export(line, env) || 1);
	if (!ft_strncmp(line, "exit", 4) && (line[4] == ' ' || !line[4]))
		return (bi_exit(line) || 1);
	return (0);
}

int	redirect_before_bi(char *line, int fd[2])
{
	int	res;

	fd[0] = dup(0);
	if (fd[0] == -1)
		return (0);
	fd[1] = dup(1);
	if (fd[1] == -1)
	{
		close(fd[0]);
		return (0);
	}
	res = redirections(line);
	if (res == -1)
		return (0);
	return (1);
}

int	restaure_redirections_bi(int fd[2])
{
	if (dup2(fd[0], 0) == -1 || dup2(fd[1], 1) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		f_exit(3);
		return (0);
	}
	close(fd[0]);
	fd[0] = -1;
	close(fd[1]);
	fd[1] = -1;
	return (1);
}


static char	**split_and_parsing(char *line)
{
	char	**argv;
	int		i;

	change_string(line, '|', -2);
	change_string(line, ' ', -1);
	argv = ft_split(line, '|');
	if (!argv)
		return (NULL);
	change_string(line, -2, '|');
	rm_useless_quotes(line);
	i = 0;
	while (argv[i])
	{
		rm_useless_quotes(argv[i]);
		i++;
	}
	return (argv);
}

void	executions(char **line, t_env **env)
{
	char	**envp;
	char	**argv;

	envp = create_envp(*env);
	if (!envp)
	{
		the_return_value(1);
		return ;
	}
	replace_all_here_docs(line, *env);
	argv = split_and_parsing(*line);
	if (!argv)
	{
		ft_strsfree(envp);
		the_return_value(1);
		return ;
	}
	if (argv[0] && (argv[1] || !(is_a_built_in(*line, env))))
		the_return_value(almost_pipex(argv, envp, (void *) env));
	ft_strsfree(envp);
	ft_strsfree(argv);
}
