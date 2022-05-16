/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:10:36 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/16 13:32:05 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		g_pid[230] = 1;
	}
}

void	handle_signals_redisplay(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_pid[230] = 1;
	}
}

void	init_signals(int redisplay)
{
	struct termios	save;

	tcgetattr(0, &save);
	save.c_lflag &= ~ECHOCTL;
	if (redisplay)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_signals_redisplay);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_signals);
	}
	tcsetattr(0, TCSANOW, &save);
}

void	exit_check(t_info *info)
{
	if (g_pid[230] == 1)
	{
		info->exit_status = 1;
		g_pid[230] = 0;
	}
}
