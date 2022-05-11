/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:48:48 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/11 14:45:35 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	current_dir(int fd)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		xperror("pwd: ");
	ft_putendl_fd(cwd, fd);
	return (0);
}
