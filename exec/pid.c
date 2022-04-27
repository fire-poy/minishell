#include "../minishell.h"

void	create_pids(t_info *info)
{
	info->pids = malloc(info->q_cmd * sizeof(int));
}

void	wait_pids(t_info *info)
{
	int	i;
	int	status;

	i = -1;
	while (++i < info->q_cmd)
		waitpid(info->pids[i], &status, 0);
	free(info->pids);
	if (WIFEXITED(status))
		info->exit_status = WEXITSTATUS(status);
}