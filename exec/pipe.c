#include "../minishell.h"

int	create_pipes(t_info *info)
{
	int	i;

	i = -1;
	info->pipes = malloc(info->pipe_i * sizeof(int *));
	if (!info->pipes)
		return (0);
	while (++i < info->pipe_i)
	{
		info->pipes[i] = malloc(2 * sizeof(int));
		if (pipe(info->pipes[i]) < 0)
		{
			perror("Error: pipe() failed");
			return (0);
		}
	}
	return (1);
}

void	free_pipes(int **pipes, int n_pipe)
{
	if (pipes && n_pipe)
	{
		while (n_pipe--)
			free(pipes[n_pipe]);
		free(pipes);
	}
}

void	close_pipes(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->pipe_i)
	{
		if (close(info->pipes[i][0]) != 0 || close(info->pipes[i][1]) != 0)
			perror("Error: pipe close() failed");
	}
	free_pipes(info->pipes, info->pipe_i);
}
