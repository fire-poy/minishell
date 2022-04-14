#include "../minishell.h"
#include <errno.h>

void    err_msg(char *e, char *avant_e, int exit_status)
{
	if (avant_e)
		ft_putstr_fd(avant_e, 2);
	perror(e);
	exit (exit_status);
}

void    err_exit(char *e, char *avant_e, int exit_status)
{
	if (avant_e)
	{
		ft_putstr_fd(e, 2);
		ft_putstr_fd(avant_e, 2);
		ft_putstr_fd("\n", 2);
	}
	exit (exit_status);
}

void	print_join(char *s1, char *s2, int fd)
{
	char	*print;

	print = ft_strjoin(s1, s2);
	if (print)
	{
		ft_putstr_fd(print, fd);
		//free(print);
	}
}

void	xperror(char *str)
{
	printf("minishell: %s: %s\n", str, strerror(errno));
}