#include "../minishell.h"

// src = split_cmd[0]
char	*ft_get_last_arg(char *src)//char **split_cmd)
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
			// free (info->split_cmd[0][0]);
			// info->split_cmd[0][0] = NULL;
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
			paths[i] = ft_strjoin(paths[i], "/");
			paths[i] = ft_strjoin(paths[i], cmd);
			if (access(paths[i], F_OK) == 0)
			{
				*path = (paths[i]);
				info->exit_status = 0;
				return (1);
			}
			free (paths[i]);
			i++;
		}
	}
	write(2, "Minishell : ", 12);
	print_join("command not found : ", cmd, 2);
	write(2, "\n", 1);
	info->exit_status = 127;
	return (0);
}
	// ft_putstr_fd("Minishell: command not found: ", 2);
	// ft_putendl_fd(cmd, 2);

// wait(&id);
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
		printf("split_cmd = %s\n", info->split_cmd[0][0]);
		if ((!ft_strcmp(info->split_cmd[0][0], "cat") || !ft_strcmp(info->split_cmd[0][0], "grep")) && info->split_cmd[0][0] != NULL)
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