#include "../minishell.h"

// int	search_type_token(*tk);
void	loop_prompt(int ac, char **av, char **envp)
{
	char	*input;
	t_env	*liste;
	t_token	*tk;
	t_info	*info;
	
	(void)ac;
	(void)av;
	liste = NULL;
	info = NULL;
 	create_env_list(&liste, envp);
	signal(SIGINT, signal_h);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		write(1, RED, ft_strlen(RED));
		input = readline("Minishell ~ ");
		write(1, DEFAULT, ft_strlen(DEFAULT));
		ft_stop(input);
		info = init_info(info);
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			tk = NULL;
			lexer(input, liste, &tk);// obtiens les token
			info = parser(liste, tk, envp, info);// obtiens cmd et infos
			execution_main(info);
			// close_all_fd(info);
			free_all(&info);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env *liste;
	int	i;

	i = 0;
	loop_prompt(ac, av, envp);
	ft_free_list(&liste);
	return (0);
}
