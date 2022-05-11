/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:16:26 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/11 17:06:33 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(t_env *env, char *name)
{
	if (!name)
		return ("$");
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

int	cd_check(char *args, t_info *liste)
{
	if (chdir(args) <= -1)
	{
		if (open(args, O_RDONLY) > 0)
		{
			cmd_err(liste, args, MSG_IS_NOT_DIRECTORY, 1);
			return (1);
		}
		cmd_err(liste, args, MSG_FILE_NOT_FOUND, 1);
		return (1);
	}
	return (0);
}

void	ft_update_dir(t_info *info)
{
	char	cwd[PATH_MAX];
	char	*dir;
	char	*pwd;

	dir = getcwd(cwd, sizeof(cwd));
	pwd = get_env(info->liste, "PWD");
	ft_env_set_content(info->liste, "OLDPWD", pwd);
	ft_env_set_content(info->liste, "PWD", dir);
}

char	*special_case(char *argv, t_info *info)
{
	char	*new_path;

	new_path = NULL;
	if (!argv || !ft_strcmp(argv, "~"))
	{
		new_path = get_env(info->liste, "HOME");
		if (!new_path)
		{
			ft_putstr_fd("minishell: cd : HOME not set\n", 2);
			info->exit_status = 1;
			return (NULL);
		}
	}
	if (argv != NULL && !ft_strcmp(argv, "-"))
	{
		new_path = get_env(info->liste, "OLDPWD");
		if (!new_path)
		{
			ft_putstr_fd("minishell: cd : OLDPWD not set\n", 2);
			info->exit_status = 1;
			return (NULL);
		}
	}
	return (new_path);
}

int	ft_cd(char **argv, t_info *info)
{
	char	*new_path;

	if (!argv[1] || !ft_strcmp(argv[1], "~") || !ft_strcmp(argv[1], "-"))
	{
		new_path = special_case(argv[1], info);
		if (new_path == NULL)
			return (1);
		if (!ft_strcmp(new_path, "\"\"") || !ft_strcmp(new_path, "\'\'"))
			return (1);
		if (cd_check(new_path, info))
			return (1);
		ft_update_dir(info);
	}
	else
	{
		if (!ft_strcmp(argv[1], "\"\"") || !ft_strcmp(argv[1], "\'\'"))
			return (1);
		if (cd_check(argv[1], info))
			return (1);
		ft_update_dir(info);
	}
	return (0);
}
