/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:27:17 by mpons             #+#    #+#             */
/*   Updated: 2022/05/13 15:32:51 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pids(t_info *info)
{
	info->pids = malloc(info->q_cmd * sizeof(int));
}

void	wait_pids(t_info *info)
{
	int	i;
	int	status;

	i = -1;
	while (++i < info->q_cmd)
		waitpid(info->pids[i], &status, 0);
	free(info->pids);
	if (WIFEXITED(status))
		info->exit_status = WEXITSTATUS(status);
}
