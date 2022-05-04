#include "../minishell.h"

int	current_dir(int fd)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		xperror("pwd: ");
	ft_putendl_fd(cwd, fd);
	return (0);
}
