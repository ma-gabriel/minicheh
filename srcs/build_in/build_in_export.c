#include "../../inc/minishell.h"
#include "../kind_of_pipex/pipex.h"

char *bi_exp_format(char *envp)
{
    char	*result;
    size_t	i;
    
    i = 0;
    while (envp[i] && envp[i] != '=')
        i++;
    result = ft_substr(envp, 0, i);
    if (!result)
        return (NULL);
    if (envp[i])
    {
        result = ft_strjoin_free_first(result, "=\"");
        if (!result)
            return (NULL);
        result = ft_strjoin_free_first(result, envp + i + 1);
        if (!result)
            return (NULL);
        result = ft_strjoin_free_first(result, "\"");
        if (!result)
            return (NULL);
    }
    return (result);
}

int bi_exp_print(t_env **env)
{
	char	**envp;
	size_t	i;
	
	i = -1;
	envp = create_envp(*env);
	if (!envp)
	{
		the_return_value(env, 1);
		return (1);
	}
	while(envp[++i])
		printf("declare -x %s\n", bi_exp_format(envp[i]));
	ft_strsfree(envp);
	the_return_value(env, 0);
	return (0);
}

int bi_export(char *line, t_env **env)
{
    char	**key_value;
    t_env	*new_lst;

    line += 7;
    while (*line == ' ')
        line++;
    if (!*line)
        return (bi_exp_print(env));
    key_value = ft_split(line, '=');
    if (!key_value)
        return (1);
    if (!key_value[1])
    {
        ft_strsfree(key_value);
        return (0);
    }
    new_lst = ft_envlstnew_frees(key_value);
    if (!new_lst)
        return (1);
    ft_envlstadd_until_sorted(env, new_lst);
    return (the_return_value(env, 0), 1);
}