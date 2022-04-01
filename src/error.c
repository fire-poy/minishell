#include "../minishell.h"

void    err_msg(char *e, char *avant_e, int exit_status)
{
	if (avant_e)
		printf("%s" ,avant_e);
	perror(e);
	exit (exit_status);
}