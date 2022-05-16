/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:15:52 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/16 10:04:49 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_pid(int id)
{
	if (id != 0)
	{
		g_pid[0] = id;
	}
}

int	ft_echo(char **argv, int fd)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	if (argv[i] != NULL)
	{
		while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
		{
			n_flag = 1;
			i++;
		}
		while (argv[i] != NULL)
		{
			ft_putstr_fd(argv[i], fd);
			if (argv[i + 1] && argv[i][0] != '\0')
				ft_putstr_fd(" ", fd);
			i++;
		}
		if (n_flag == 1)
			return (0);
	}
	ft_putstr_fd("\n", fd);
	return (0);
}
