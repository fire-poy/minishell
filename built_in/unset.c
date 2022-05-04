#include "../minishell.h"

void	ft_unset(t_env **env, char *argv)
{
	if (argv)
	{
		ft_delete_from_list(env, argv);
	}
}
