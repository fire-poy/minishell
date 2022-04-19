#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	loop_prompt(ac, av, envp);
	return (0);
}
