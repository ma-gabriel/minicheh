#include "../inc/minishell.h"

char    *get_pwd(void)
{
	char    *path;
	size_t  i;

	i = 1;
	path = NULL;
	errno = 34;
	while (errno == 34)
	{
		if (path)
			free(path);
		errno = 0;
		path = malloc(i);
		if (!path)
			return (NULL);
		getcwd(path, i);
		i++;
	}
	if (!errno)
		return (path);
	if (path)
		free(path);
	perror("pwd");
	return (NULL);
}


int	bi_pwd(t_env **env)
{
	char *pwd_string;

	pwd_string = get_pwd();
	if (!pwd_string)
	{
		the_return_value(env, 1);
		return (1);
	}
	printf("%s\n", pwd_string);
	free(pwd_string);
	the_return_value(env, 0);
	return (0);
}
