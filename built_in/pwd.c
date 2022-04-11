#include "../minishell.h"


int	current_dir(void)
{
	char cwd[PATH_MAX];

  if (!getcwd(cwd, sizeof(cwd)))
		xperror("pwd: ");
	ft_putendl_fd(cwd, 2);
	return (0);
}
