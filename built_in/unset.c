#include "../minishell.h"

void	ft_unset(t_env **env, char *argv)
{
	/*int	i;

	i = 0;
	while(argv[i])
	{
		printf("Unset = %s\n", argv[i++]);
	}*/
	//printf("argv[0] = %s\n", argv);
	if (argv)
	{
		//printf("I am Unset %s\n", argv);
		ft_delete_from_list(env, argv);
	}
}