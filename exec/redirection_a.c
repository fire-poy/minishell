/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:27:36 by mpons             #+#    #+#             */
/*   Updated: 2022/05/04 17:52:22 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_rdonly_close(t_info *info, t_token *tk, int last_in)
{
	int	fd;

	fd = open(tk->content, O_RDONLY, 0644);
	if (fd == -1)
	{
		cmd_err(info, tk->content, MSG_FILE_NOT_FOUND, 1);
		exit(1);
	}
	if (last_in == tk->in_index)
		return (fd);
	else
		close(fd);
	return (0);
}

int	redirect_in(t_info *info, int i)
{
	t_token	*tk;
	int		fd_in;
	int		last_in;

	tk = info->tk;
	last_in = find_last_in(tk, i);
	while (tk && tk->cmd_index <= i)
	{
		if (tk->type == IN_FILE && tk->cmd_index == i)
			fd_in = open_rdonly_close(info, tk, last_in);
		if (tk->type == HEREDOC && tk->cmd_index == i)
		{
			if (last_in == tk->in_index)
				fd_in = get_heredoc_fd(i);
		}
		tk = tk->next;
	}
	return (fd_in);
}

// return fd_out
int	redirect_out(t_info *info, int i)
{
	t_token	*tk;
	int		fd_out;
	int		last_out;

	tk = info->tk;
	last_out = find_last_out(tk, i);
	while (tk)
	{
		if (tk->type == OUT_FILE && tk->cmd_index == i)
			fd_out = open_trunc_close(tk, last_out);
		if (tk->type == APPEND && tk->cmd_index == i)
		{
			fd_out = open(tk->content, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (last_out == tk->out_index)
				break ;
			else
				close(fd_out);
		}
		tk = tk->next;
	}
	return (fd_out);
}

// changer fd_in info?
void	redirect_in_out(t_info *info, int i)
{
	int	fd_in;
	int	fd_out;
	int	last_cmd;

	last_cmd = info->cmd_i;
	if (get_q_in(info->tk, i) > 0)
	{
		fd_in = redirect_in(info, i);
		dup2(fd_in, STDIN_FILENO);
		close (fd_in);
	}
	else if (info->q_cmd > 1 && i != 0)
	{
		dup2(info->pipes[i - 1][0], STDIN_FILENO);
	}
	if (get_q_out(info->tk, i) > 0)
	{
		fd_out = redirect_out(info, i);
		dup2(fd_out, STDOUT_FILENO);
		close (fd_out);
	}
	else if (info->q_cmd > 1 && i != last_cmd)
		dup2(info->pipes[i][1], STDOUT_FILENO);
}
