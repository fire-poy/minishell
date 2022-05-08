/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:46:22 by mpons             #+#    #+#             */
/*   Updated: 2022/05/04 19:24:18 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_last_arg(char *src)
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

int	slash_case(char *cmd, t_info *info, int i)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if ((access(cmd, X_OK) == -1))
				return (2);
			free (info->split_cmd[i][0]);
			info->split_cmd[i][0] = NULL;
			info->split_cmd[i][0] = ft_get_last_arg(cmd);
			return (1);
		}
	}
	return (0);
}

int	check_path(char *cmd, t_info *info, char **path, char *env)
{
	char	**paths;
	int		i;

	i = 0;
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
	return (0);
}

// return 1 if access == ok
// return the good path by **path
int	access_ok(char *cmd, t_info *info, char **path, int i)
{
	char	*env;

	if (is_invalid_command(info, cmd))
		return (0);
	if (slash_case(cmd, info, i) == 2)
	{
		cmd_err(info, cmd, MSG_PERMISSION_DENIED, 126);
		return (0);
	}
	if (slash_case(cmd, info, i) == 1)
	{
		*path = cmd;
		return (1);
	}
	env = chercher_env(info->liste, "PATH");
	if (env != NULL)
	{
		if (check_path(cmd, info, path, env))
			return (1);
	}
	cmd_err(info, cmd, MSG_COMMAND_NOT_FOUND, 127);
	return (0);
}
