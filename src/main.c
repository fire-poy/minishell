#include "../minishell.h"

char	*prompt(void)
{
	char *s;

	write(1, RED, ft_strlen(RED));
	s = readline("Minishell ~ ");
	write(1, DEFAULT, ft_strlen(DEFAULT));
	return (s);
}

void	loop_prompt(t_env *liste, char **envp)
{
	char	*input;
	t_token	*tk;
	t_info	*info;
	int last_exit;
	
	info = NULL;
	last_exit = 0;
	signal(SIGINT, signal_h);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = prompt();
		ft_stop(input);
		info = init_info(info, last_exit);
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			tk = NULL;
			lexer(input, liste, &tk, info);// obtiens les token
			info = parser(liste, tk, envp, info);// obtiens cmd et infos
			create_heredocs(info->tk);
			execution_main(info);
			destroy_heredocs(info->q_cmd);
			last_exit = info->exit_status;
			free_all(info);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env *liste;
	int	i;

	(void)ac;
	(void)av;
	i = 0;
 	create_env_list(&liste, envp);
	loop_prompt(liste, envp);
	ft_free_list(&liste);
	while (1)
		pause();
	return (0);
}
