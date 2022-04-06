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
	char    *message;
	int     estatus;

	check_arg(arg);
	estatus = ft_atoi(arg);
	if (estatus < 0)
	{
		message = ft_strjoin(arg, ": numeric argument required");
		err_exit("exit: ", message, 255);
	}
	return (estatus);
}


int ft_exit(char **liste_args)
{
    int     i;
    char    *arg;

    arg = malloc(sizeof(char) * ft_strlen(liste_args[0]));
    arg = ft_strdup(liste_args[0]);
    if (!arg)
    {
    // if I am in a forked shell i need to print èxit``
    // how can I identify that?
        exit(0);
    }
    if (liste_args[1] != NULL)
        err_exit("exit", ":too many arguments", 1);
    i = exit_arg(arg);
    free (arg);
    //free(liste_args);
    exit(i);
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        printf("%s\n", argv[1]);
        ft_exit(&argv[1]);
    }
    return (0);
}