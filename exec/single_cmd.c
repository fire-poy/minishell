#include "../minishell.h"

// return 1 if access == ok
// return the good path by **path
int	access_ok(char *cmd, t_info *info, char **path)
{
	char	**paths;
	char	*env;
	int		i;

	env = chercher_env(info->liste, "PATH");
	paths = ft_split(env, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (access(paths[i], 0) == 0)
		{
			*path = (paths[i]);
			return (1);
		}
		free (paths[i]);
		i++;
	}
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	return (0);
}

int	exec_single_cmd(t_info *info)
{
	int		id;
	int		status;
	char	*path;

	id = 0;
	path = NULL;
	if (is_builtin(info->split_cmd[0][0]))
		exec_builtin(info->split_cmd[0], info->liste);
	else
	{
		if (access_ok(info->split_cmd[0][0], info, &path))
			id = fork();
		if (id == 0)
		{
			// redirect_in_out(info);
			execve(path, info->split_cmd[0], info->envp);
		}
		else
		{
			// wait(&id);
			free (path);
			waitpid(id, &status, 0);
			if (WIFEXITED(status))
			info->exit_status = WEXITSTATUS(status);
		}
	}
	return (1);
}
