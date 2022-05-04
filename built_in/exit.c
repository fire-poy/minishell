/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:51:16 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/04 18:52:25 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_arg(char	*arg)
{
	char	*message;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			message = ft_strjoin(arg, ": numeric argument required");
			err_exit("minishell: exit: ", message, 255);
			return (0);
		}
		i++;
	}
	return (1);
}

int	exit_arg(char *arg)
{
	int	estatus;

	if (check_arg(arg) == 0)
		return (0);
	estatus = ft_atoi(arg);
	return (estatus);
}

void	ft_exit(char **tab_cmd, t_info *info)
{
	int	i;

	if (tab_cmd[1] == NULL)
	{
		printf("exit\n");
		ft_free_list(&info->liste);
		free_all(info);
		exit(0);
	}
	if (tab_cmd[2] != NULL)
	{
		printf("Minishell: exit :too many arguments\n");
		return ;
	}
	i = exit_arg(tab_cmd[1]);
	printf("exit\n");
	ft_free_list(&info->liste);
	free_all(info);
	exit(i);
}
