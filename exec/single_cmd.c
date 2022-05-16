/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:32:00 by mpons             #+#    #+#             */
/*   Updated: 2022/05/16 13:13:41 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_init(t_info *info, int id)
{
	if ((!ft_strcmp(info->split_cmd[0][0], "cat") || !ft_strcmp
		(info->split_cmd[0][0], "grep") || !ft_strcmp
		(info->split_cmd[0][0], "wc")) && info->split_cmd[0][0] != NULL)
	{
		ft_get_pid(id);
		signal(SIGINT, signal_q);
		signal(SIGQUIT, signal_q);
	}
	else
	{
		ft_get_pid(id);
		init_signals(0);
	}
}

void	exec_parent_and_child(t_info *info, int id, char *path)
{
	int	status;

	if (id == 0)
	{
		redirect_in_out(info, 0);
		execve(path, info->split_cmd[0], info->envp);
	}
	else
	{
		free (path);
		waitpid(id, &status, 0);
		if (WIFEXITED(status))
			info->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			info->exit_status = 130;
	}
}

int	exec_single_cmd(t_info *info)
{
	int		id;
	char	*path;
	int		fd;

	id = 0;
	path = NULL;
	if (is_builtin(info->split_cmd[0][0]))
	{
		fd = redirect_in_out_bi(info, 0);
		if (fd > 0)
			info->exit_status = exec_builtin(info->split_cmd[0], info, fd);
	}
	else if (access_ok(info->split_cmd[0][0], info, &path, 0))
	{
		id = fork();
		signal_init(info, id);
		exec_parent_and_child(info, id, path);
	}
	return (1);
}
