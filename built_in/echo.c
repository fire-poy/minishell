#include "../minishell.h"

int	ft_echo(char **argv)
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
			// printf("%s", argv[i]);
			ft_putstr_fd(argv[i]);
			if (argv[i + 1] && argv[i][0] != '\0')
				printf(" ");
			i++;
		}
		if (n_flag == 1)
			return (0);
	}
	printf("\n");
	return (0);
}



// compilation = gcc built_in/echo.c libft/ft_strncmp.c && ./a.out
// int	main(int argc, char **argv)
// {
// 	if (strncmp(argv[1], "echo", 5))
// 		return (ft_echo(argv, argc));
// 	return (0);
// }
