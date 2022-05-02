#include "../minishell.h"
#include "../libft/libft.h"

int	check_arg(char	*arg)
{
	char	*message;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			message = ft_strjoin(arg, ": numeric argument required");
			err_exit("minishell: exit: ", message, 255);
			return (0);
		}
		i++;
	}
	return (1);
}

int	exit_arg(char *arg)
{
	int     estatus;

	if (check_arg(arg) == 0)
		return (0);
	estatus = ft_atoi(arg);
	return (estatus);
}


void	ft_exit(char **tab_cmd)
{
  int     i;

  if (tab_cmd[1] == NULL)
	{
		printf("exit\n");
    exit(0);
	}
  if (tab_cmd[2] != NULL)
	{
		printf("Minishell: exit :too many arguments\n");
		return ;
	}
  i = exit_arg(tab_cmd[1]);
	printf("exit\n");
	// free_all(info);
	// ft_free_list;
  exit(i);
}
