#include "../minishell.h"

int	my_env(t_env	*envp)
{
  while (envp->next != NULL)
	{
		printf("%s\n", envp->initial_env);
		envp = envp->next;
	}
	return (0);
}
