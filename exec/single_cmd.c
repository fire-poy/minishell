#include "../minishell.h"

char	*ft_get_last_arg(char *src)
{
	int	i;
	int j;
	int	dst_len;
	char *dst;

	i = ft_strlen(src) - 1;
	dst_len = 0;
	while (src[i] != '/')
	{
		dst_len++;
		i--;
	}
	j = 0;
	i++;
	dst = malloc(sizeof(char) * ft_strlen(src) + 1);
	while (src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (dst);
}


int	slash_case(char *cmd, t_info *info)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			info->split_cmd[0][0] = ft_get_last_arg(cmd);
			return (1);
		}
	}
	return (0);
}
		 
// return 1 if access == ok
// return the good path by **path
int	access_ok(char *cmd, t_info *info, char **path)
{
	char	**paths;
	char	*env;
	int		i;

	i = 0;
	if (slash_case(cmd, info))
	{
		*path = cmd;
		return (1);
	}
	env = chercher_env(info->liste, "PATH");
	paths = ft_split(env, ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (access(paths[i], F_OK) == 0)
		{
			*path = (paths[i]);
			return (1);
		}
		free (paths[i]);
		i++;
	}
	ft_putstr_fd("Minishell: command not found: ", 2);
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
		exec_builtin(info->split_cmd[0], info);
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
