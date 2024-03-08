#include "../inc/minishell.h"

int     cd(char *path)
{
	int     res;

	if (!path)
		return (0);
	res = chdir(path);
	if (!res)
		return (0);
	perror("cd");
	return (-1);
}
int	change_pwd_env(t_env **env)
{
	char	*pwd;
	char	*litterally_pwd;
	t_env	*temp;

	pwd = get_pwd();
	if (!pwd)
		return (2);
	litterally_pwd = ft_strdup("PWD");
	if (!litterally_pwd)
		free(pwd);
	if (!litterally_pwd)
		return (3);
	temp = ft_envlstnew(litterally_pwd, pwd);
	if (!temp)
	{
		free(pwd);
		free(litterally_pwd);
		return (4);
	}
	ft_envlstadd_until_sorted(env, temp);
	return (0);
}

int	bi_cd(char *line, t_env **env)
{
	int res;

	line += 2;
	while (*line == ' ')
		line++;
	res = cd(line);
	if (res)
	{
		the_return_value(env, 1);
		return (1);
	}
	res = change_pwd_env(env);
	the_return_value(env, res);
	return (res);	
}
