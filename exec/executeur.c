/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:58:58 by mpons             #+#    #+#             */
/*   Updated: 2022/05/25 10:38:17 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_child_proc(t_info *info, int i)
{
	char	*path;

	path = NULL;
	info->pids[i] = fork();
	if (info->pids[i] < 0)
		perror("Error: fork() failed");
	if (info->pids[i] == 0)
	{
		redirect_in_out(info, i);
		close_pipes(info);
		if (info->full_cmd[i][0] != '\0')
		{
			if (is_builtin(info->split_cmd[i][0]))
				exec_builtin(info->split_cmd[i], info, 1);
			else if (access_ok(info->split_cmd[i][0], info, &path, i))
			{
				if (execve(path, info->split_cmd[i], info->envp))
					cmd_err(info, info->split_cmd[0][0],
						strerror(errno), errno);
			}
		}
		exit(info->exit_status);
	}
}

void	exec_cmds(t_info *info)
{
	int	i;

	create_pids(info);
	create_pipes(info);
	i = -1;
	while (++i < info->q_cmd)
	{
		exec_child_proc(info, i);
	}
	close_pipes(info);
	wait_pids(info);
}

void	execution_main(t_info *info)
{
	int	id;
	int	status;

	if (info->q_cmd == 1)
	{
		if (info->full_cmd[0][0] == '\0')
		{
			id = fork();
			if (id == 0)
			{	
				redirect_in_out(info, 0);
				exit(0);
			}
			else
			{
				waitpid(id, &status, 0);
				if (WIFEXITED(status))
					info->exit_status = WEXITSTATUS(status);
			}
		}
		else
			exec_single_cmd(info);
	}
	else
		exec_cmds(info);
}
