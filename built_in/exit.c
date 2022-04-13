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


void	ft_exit(t_token *liste_args)
{
  int     i;
  t_token	*args;

  args = liste_args;
  if (args->tab_cmd[1] == NULL)
	{
		printf("exit\n");
    exit(0);
	}
  if (args->tab_cmd[2] != NULL)
	{
		printf("exit :too many arguments\n");
		return ;
	}
  i = exit_arg(args->tab_cmd[1]);
	printf("exit\n");
  exit(i);
}
