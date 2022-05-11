/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:15:52 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/11 14:12:30 by jhermon-         ###   ########.fr       */
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

int	ft_echo_quotes(t_info *liste, int fd)
{
	int		i;
	int		k;
	int		j;
	char	c;

	i = 0;
	k = -1;
	j = 0;
	while (liste->input[j] == ' ')
		j++;
	while (liste->input[++k])
	{
		c = detect_and_check_quotes(liste->input, &i);
		if (liste->input[j] == c && (c == '\'' || c == '\"'))
		{
			cmd_err(liste, liste->full_cmd[0], "command not found", 127);
			return (0);
		}
		if (ft_check_c(c, liste, i, fd) == 0)
			return (0);
	}
	return (1);
}

void	ft_print_echo(char **argv, int i, int fd, int size)
{
	while (argv && argv[i])
	{
		ft_putstr_fd(argv[i++], fd);
		ft_putstr_fd(" ", fd);
	}
	if (i < size)
		ft_putstr_fd(" ", fd);
	i = 1;
	if (str_compare(argv[i], "-n") != 0)
		ft_putendl_fd("", fd);
}

int	ft_echo(char **argv, int fd, t_info *liste)
{
	int	i;
	int	size;

	i = 1;
	size = 0;
	if (ft_echo_quotes(liste, fd) == 0)
		return (0);
	if (argv)
		size = array_length(argv);
	if (size > 1)
	{
		if (str_compare(argv[i], "-n") == 0)
			i++;
		ft_print_echo(argv, i, fd, size);
	}
	else
		ft_putendl_fd("", fd);
	return (0);
}
