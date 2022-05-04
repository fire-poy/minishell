/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:36:54 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/04 18:36:58 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_env(t_env *envp, int fd)
{
	while (envp != NULL)
	{
		ft_putstr_fd(envp->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(envp->content, fd);
		ft_putstr_fd("\"\n", fd);
		envp = envp->next;
	}
	return (0);
}
