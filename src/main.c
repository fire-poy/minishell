#include "../minishell.h"

t_info	*init_info(t_env *liste, char **envp, int last_exit)
{
	t_info *info;

	info = NULL;
	info = malloc (sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->tk = NULL;
	info->liste = liste;
	info->envp = envp;
	info->full_cmd = NULL;
	info->split_cmd = NULL;
	info->q_in = 0;
	info->q_out = 0;
	info->cmd_i = 0;
	info->pipe_i = 0;
	info->q_cmd = 0;
	info->err = 0;
	info->pipes = NULL;
	info->pids = NULL;
	info->exit_status = last_exit;
	return (info);
}

char	*prompt(void)
{
	char	*s;

	write(1, RED, ft_strlen(RED));
	s = readline("Minishell ~ ");
	write(1, DEFAULT, ft_strlen(DEFAULT));
	return (s);
}

int	parsing_execution_and_free(char *input, t_info *info)
{
	int	last_exit;

	last_exit = 0;
	if (lexer(input, info) == 0)
	{
		if (info->err == 0)
			xperror("quotes pas bien fermés");
		last_exit = info->exit_status;
		free_info_simple(info);
		free (input);
	}
	else
	{	
		parser(info);
		create_heredocs(info->tk);
		execution_main(info);
		destroy_heredocs(info->q_cmd);
		last_exit = info->exit_status;
		free_all(info);
		free (input);
	}
	return (last_exit);
}

void	loop_prompt(t_env *liste, char **envp)
{
	char	*input;
	t_info	*info;
	int		last_exit;

	info = NULL;
	last_exit = 0;
	signal(SIGINT, signal_h);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = prompt();
		add_history(input);
		ft_stop(input);
		info = init_info(liste, envp, last_exit);
		if (ft_strlen(input) > 0)
			last_exit =	parsing_execution_and_free(input, info);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*liste;
	int		i;

	(void)ac;
	(void)av;
	i = 0;
	liste = NULL;
	create_env_list(&liste, envp);
	loop_prompt(liste, envp);
	ft_free_list(&liste);
	while (1)
		pause();
	return (0);
}
