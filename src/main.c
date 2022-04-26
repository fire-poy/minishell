#include "../minishell.h"

// int	search_type_token(*tk);
void	loop_prompt(int ac, char **av, char **envp)
{
	char	*input;
	t_env	*liste;
	t_token	*tk;
	t_info	*info;
	
	if (!ac || !av || !envp)
		return ;
	liste = NULL;
 	create_env_list(&liste, envp);
	signal(SIGINT, signal_h);
	signal(SIGQUIT, signal_h);
	while (1)
	{
		write(1, RED, ft_strlen(RED));
		input = readline("Minishell ~ ");
		write(1, DEFAULT, ft_strlen(DEFAULT));
		ft_stop(input);
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			tk = NULL;
			lexer(input, liste, &tk);// obtiens les token
			info = parser(liste, tk, envp);// obtiens cmd et infos
			execution_main(info);
			// close_all_fd(info);
			free_all(&info);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	(void) av;
	loop_prompt(ac, av, envp);
	return (0);
}
