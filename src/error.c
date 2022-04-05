#include "../minishell.h"

void    err_msg(char *e, char *avant_e, int exit_status)
{
	if (avant_e)
		ft_putstr_fd(avant_e, 2);
	perror(e);
	exit (exit_status);
}