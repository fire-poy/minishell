#include "../minishell.h"

void	ft_unset(t_env **env, char **argv)
{
	/*int	i;

	i = 0;
	while(argv[i])
	{
		printf("Unset = %s\n", argv[i++]);
	}*/
	if (argv[1])
	{
		//printf("I am Unset\n");
		ft_delete_from_list(env, argv[1]);
	}
}