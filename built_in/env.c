#include "../minishell.h"

void	my_env(char **envp)
{
	int index = 0;

  while (envp[index])
    printf("%s\n", envp[index++]);
}
