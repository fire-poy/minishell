#include "../minishell.h"


void	current_dir(void)
{
	char cwd[PATH_MAX];

  if (!getcwd(cwd, sizeof(cwd)))
		xperror("pwd: ");
	 	t_env *head;
	ft_putendl_fd(cwd, 2);
}
