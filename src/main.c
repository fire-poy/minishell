/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:40:16 by mpons             #+#    #+#             */
/*   Updated: 2022/05/16 12:01:03 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_info	*init_info(t_env *liste, int last_exit, char *input)
{
	t_info	*info;

	info = NULL;
	info = malloc (sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->tk = NULL;
	info->liste = liste;
	info->envp = get_env_tab(liste);
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
	info->input = input;
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
			ft_putendl_fd("minishell: quotes pas bien fermés", 2);
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

void	loop_prompt(t_env *liste)
{
	char	*input;
	t_info	*info;
	int		last_exit;

	info = NULL;
	last_exit = 0;
	while (1)
	{
		init_signals(1);
		input = prompt();
		add_history(input);
		init_signals(0);
		ft_stop(input, last_exit);
		info = init_info(liste, last_exit, input);
		if (ft_strlen(input) > 0)
			last_exit = parsing_execution_and_free(input, info);
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
	loop_prompt(liste);
	ft_free_list(&liste);
	while (1)
		pause();
	return (0);
}
