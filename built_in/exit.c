#include "../minishell.h"
#include "../libft/libft.h"

void	check_arg(char	*arg)
{
	char	*message;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			message = ft_strjoin(arg, ": numeric argument required");
			err_exit("exit: ", message, 255);
		}
		i++;
	}
}

int	exit_arg(char *arg)
{
	int     estatus;

	check_arg(arg);
	estatus = ft_atoi(arg);
	return (estatus);
}


void	ft_exit(t_token *liste_args)
{
  int     i;
  t_token	*args;

  args = liste_args;
	printf("exit\n");
  if (args->tab_cmd[1] == NULL)
    exit(0);
  if (args->tab_cmd[2] != NULL)
	{
		printf("minishell: exit :too many arguments\n");
		return ;
	}
  i = exit_arg(args->tab_cmd[1]);
	//return (printf(" exit stat = %d\n", i));
  exit(i);
	//return (0);
}

// int main(int argc, char **argv)
// {
//     if (argc > 1)
//     {
//         printf("%s\n", argv[1]);
//         ft_exit(&argv[1]);
//     }
//     return (0);
// }