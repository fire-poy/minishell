/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:49:35 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/16 12:02:32 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	return (0);
}

int	exec_builtin(char **tab_cmd, t_info *liste, int fd)
{
	if (!ft_strcmp(tab_cmd[0], "exit"))
	{
		ft_exit(tab_cmd, liste);
		return (1);
	}
	else if (!ft_strcmp(tab_cmd[0], "pwd") || !ft_strcmp(tab_cmd[0], "PWD"))
		return (current_dir(fd));
	else if (!ft_strcmp(tab_cmd[0], "cd"))
		return (ft_cd(tab_cmd, liste));
	else if (!ft_strcmp(tab_cmd[0], "echo") || !ft_strcmp(tab_cmd[0], "ECHO"))
		return (ft_echo(tab_cmd, fd));
	else if (!ft_strcmp(tab_cmd[0], "env") || !ft_strcmp(tab_cmd[0], "ENV"))
		return (my_env(liste->liste, fd));
	else if (!ft_strcmp(tab_cmd[0], "unset"))
		return (ft_unset(&liste->liste, tab_cmd[1]));
	else if (!ft_strcmp(tab_cmd[0], "export"))
		return (ft_export(tab_cmd, liste->liste, liste, fd));
	return (0);
}
