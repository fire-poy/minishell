#include "../minishell.h"

int	my_env(t_env	*envp)
{
  while (envp != NULL)
	{
		printf("%s=", envp->name);
		printf("%s\n", envp->content);
		envp = envp->next;
	}
	return (0);
}
