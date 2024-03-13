#include "../inc/minishell.h"

int	sig;

void	get_sig(int signal)
{
	if (SIGQUIT == signal)
	{
		;
	}
	if (SIGINT == signal)
	{
		sig = 1;
	}
}
