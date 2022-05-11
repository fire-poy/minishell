/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:08:53 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/11 14:13:33 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	array_length(char *arr[])
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int	str_compare(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	ft_check_c(char c, t_info *liste, int i, int fd)
{
	int	size;

	size = ft_strlen(liste->input);
	if (c == '\'' || c == '\"')
	{
		while (str_compare(liste->input, "echo ") == 0)
		{
			i++;
		}
		i++;
		while (i < size - 1)
		{
			ft_putchar_fd(liste->input[i], fd);
			i++;
		}
		write(fd, "\n", 1);
		return (0);
	}
	return (1);
}
