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
				exec_builtin(info->split_cmd[i], info);
			else if (access_ok(info->split_cmd[i][0], info, &path))
			{
				if (execve(path, info->split_cmd[i], info->envp))
					err_msg("comand error", NULL, info->exit_status);
			//show_command_error(info, cmd->name, strerror(errno), errno);//err_msg
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
