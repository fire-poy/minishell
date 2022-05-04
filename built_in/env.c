#include "../minishell.h"

int	my_env(t_env *envp, int fd)
{
  while (envp != NULL)
	{
		ft_putstr_fd(envp->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(envp->content, fd);
		ft_putstr_fd("\n", fd);
		envp = envp->next;
	}
	return (0);
}
// printf("%s=", envp->name);
// printf("\"%s\"\n", envp->content);
