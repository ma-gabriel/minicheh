#include "../inc/minishell.h"

void get_sig(int sig)
{
    if (SIGQUIT == sig)
    {
        ;
    }
    if (SIGINT == sig) {
        printf("\n");  // Aller à la ligne après le signal SIGINT
        write(1, "MiniCheh -> " , 13);
    }
}