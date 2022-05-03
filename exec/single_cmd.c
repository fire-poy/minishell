#include "../minishell.h"

char	*ft_get_last_arg(char *src)//char **split_cmd)
{
	int		i;
	int		j;
	int		dst_len;
	char	*dst;

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
	if (is_invalid_command(info, cmd))
		return (0);
	if (slash_case(cmd, info))
	{
		*path = cmd;
		return (1);
	}
	env = chercher_env(info->liste, "PATH");
	if (env != NULL)
	{
		paths = ft_split(env, ':');
		while (paths[i])
		{
			*path = ft_strjoin(paths[i], "/");
			*path = ft_strjoin_free(*path, cmd);
			if (access(*path, F_OK) == 0)
			{
				free_tab(paths);
				info->exit_status = 0;
				return (1);
			}
			free(*path);
			i++;
		}
		free_tab(paths);
	}
	info->exit_status = show_command_error(info, cmd, MSG_COMMAND_NOT_FOUND, 127);
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
		info->exit_status = exec_builtin(info->split_cmd[0], info);
	else if (access_ok(info->split_cmd[0][0], info, &path))
	{
		id = fork();
		if ((!ft_strcmp(info->split_cmd[0][0], "cat") || !ft_strcmp
		(info->split_cmd[0][0], "grep")) && info->split_cmd[0][0] != NULL)
		{
			ft_get_pid(id);
			signal(SIGINT, signal_q);
			signal(SIGQUIT, signal_q);
		}
		else
		{
			ft_get_pid(id);
			signal(SIGINT, signal_h);
			signal(SIGQUIT, SIG_IGN);
		}
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
		}
	}
	return (1);
}
