#include "../minishell.h"

int	ft_echo(char **argv, int fd)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	if (argv[i] != NULL)
	{
		while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
		{
			n_flag = 1;
			i++;
		}
		while (argv[i] != NULL)
		{
			ft_putstr_fd(argv[i], fd);
			if (argv[i + 1] && argv[i][0] != '\0')
				ft_putstr_fd(" ", fd);
			i++;
		}
		if (n_flag == 1)
			return (0);
	}
	ft_putstr_fd("\n", fd);
	return (0);
}
