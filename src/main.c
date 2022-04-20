#include "../minishell.h"

// int	search_type_token(*tk);
void	loop_prompt(int ac, char **av, char **envp)
{
	char		*input;
	t_env		*liste;
	t_token		*tk;
	
	if (!ac || !av || !envp)
		return ;
	liste = NULL;
 	create_env_list(&liste, envp);
	while (1)
	{
		write(1, GREEN, ft_strlen(GREEN));
		input = readline("Minishell > ");
		write(1, DEFAULT, ft_strlen(DEFAULT));
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			tk = NULL;
			lexer(input, liste, &tk);// obtiene los token
			parser(liste, tk, envp);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	loop_prompt(ac, av, envp);

	return (0);
}
